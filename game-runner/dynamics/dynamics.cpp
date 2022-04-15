#include "dynamics.h"

void updateMarple(Marple *marple, MPU6050 *gyro, bool debug, float bounce_loss) {
    if (marple== nullptr) {
        return;
    }
    float x, y, z;
    float weighting_factor = 0.1;
    gyro->getAccel(&x, &y, &z);
    // clip outliers
    if (x >= 2 or x <= -2) x = 0;
    if (y >= 2 or y <= -2) y = 0;
    if (z >= 2 or z <= -2) z = 0;
    marple->x_acceleration = x * weighting_factor;
    marple->y_acceleration = y * weighting_factor;
    // apply calculated values
    int x_pos = std::round(marple->getPos()[0]), y_pos = std::round(marple->getPos()[1]);
    int diameter = marple->getDiameter();

    // ---------------------------------------------------------------------------------------
    for (int cur = 0; cur < diameter; cur++) {
        if (((x_pos + diameter + 1) <= 64 && (x_pos - 1) >= 0)) { // check left X
            if (Object::frame[x_pos - 1][y_pos + cur] &&
                Object::frame[x_pos - 1][y_pos + cur]->getType() == WALL) {
                if (marple->x_acceleration < 0) {
                    marple->x_acceleration = 0;
                }
                if (marple->x_velocity < 0) {
                    marple->x_velocity *= -1;
                }
                if (marple->x_velocity < 0.1) {
                    marple->x_velocity = 0;
                }
                marple->x_velocity *= bounce_loss;
                if (debug) std::cout << "BOUNCE : LEFT x-\n";
            }

            if (Object::frame[x_pos + diameter + 1][y_pos + cur] && // check right X
                Object::frame[x_pos + diameter + 1][y_pos + cur]->getType() == WALL) {
                if (marple->x_acceleration > 0) {
                    marple->x_acceleration = 0;
                }
                if (marple->x_velocity > 0) {
                    marple->x_velocity *= -1;
                }
                if (marple->x_velocity > 0.1) {
                    marple->x_velocity = 0;
                }
                marple->x_velocity *= bounce_loss;
                if (debug) std::cout << "BOUNCE : RIGHT x+\n";
            }
        }
        else {
            marple->x_velocity = 0;
            marple->x_acceleration = 0;
        }


        if (((y_pos + diameter + 1) <= 64 && (y_pos - 1) >= 0)) { // check above Y
            if (Object::frame[x_pos + cur][y_pos - 1] &&
                Object::frame[x_pos + cur][y_pos - 1]->getType() == WALL) {
                if (marple->y_acceleration < 0) {
                    marple->y_acceleration = 0;
                }
                if (marple->y_velocity < 0) {
                    marple->y_velocity *= -1;
                }
                marple->y_velocity *= bounce_loss;
                if (debug) std::cout << "BOUNCE : UP y-\n";
            }


            if (Object::frame[x_pos + cur][y_pos + diameter + 1] && // check below Y
                Object::frame[x_pos + cur][y_pos + diameter + 1]->getType() == WALL) {
                if (marple->y_acceleration > 0) {
                    marple->y_acceleration = 0;
                }
                if (marple->y_velocity > 0) {
                    marple->y_velocity *= -1;
                }
                marple->y_velocity *= bounce_loss;
                if (debug) std::cout << "BOUNCE : DOWN y+\n";
            }
        }
        else {
            marple->y_velocity = 0;
            marple->y_acceleration = 0;
        }
    }
    // ---------------------------------------------------------------------------------------

    marple->x_velocity += (marple->x_acceleration);
    marple->y_velocity += (marple->y_acceleration);
    marple->move(marple->x_velocity, marple->y_velocity);
    if (debug) {
        std::cout << "x_acc: " << marple->x_acceleration << ", y_acc: " << marple->y_acceleration << " || ";
        std::cout << "x_vel: " << marple->x_velocity << ", y_vel: " << marple->y_velocity << "\n";
    }
}