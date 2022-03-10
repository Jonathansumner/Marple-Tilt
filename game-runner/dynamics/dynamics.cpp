
#include "dynamics.h"
#include "../graphics/gfx.h"
#include <iostream>
#include "MPU6050.h"

void updateMarple(Marple *marple, MPU6050 *gyro, const vector <bool>& debug) {
    float x, y, z;
//    float weighting_factor = 1;
    float x_pos = marple->getPos()[0], y_pos = marple->getPos()[1];
////    gyro->getGyro(&x, &y, &z);
//    if (x >= 20 or x <= -20) x = 0; // clip outliers
//    if (y >= 20 or y <= -20) y = 0;
//    if (z >= 20 or z <= -20) z = 0;
//    marple->x_acceleration = x * weighting_factor;
//    marple->y_acceleration = y * weighting_factor;
    //apply calculated values
    handleCollision(marple, debug[1]);
    marple->x_velocity += (marple->x_acceleration);
    marple->y_velocity += (marple->y_acceleration);
    marple->move(marple->x_velocity, marple->y_velocity);
    if (debug[0]) {
        std::cout << "pos: " << x_pos << ", " << y_pos << "\n";
        std::cout << "gyro: " << x << ", " << y << "\n";
        std::cout << "x_acc: " << marple->x_acceleration << ", y_acc: " << marple->y_acceleration << "\n";
        std::cout << "x_vel: " << marple->x_velocity << ", y_vel: " << marple->y_velocity << "\n";
    }
}

void handleCollision(Marple *marple, bool debug) {
    int x_pos = round(marple->getPos()[0]), y_pos = round(marple->getPos()[1]);
    int diameter = marple->getDiameter();
    for (int cur = 0; cur < diameter; cur++) {
        if (((x_pos + diameter + 1) <= 64 && (x_pos - 1) >= 0)) {
            if ((Object::frame[x_pos - 1][y_pos + cur] &&
                 Object::frame[x_pos - 1][y_pos + cur]->getType() == WALL) or
                (Object::frame[x_pos + diameter + 1][y_pos + cur] &&
                 Object::frame[x_pos + diameter + 1][y_pos + cur]->getType() == WALL)) {
                marple->x_velocity *= -1;
//                marple->x_velocity *= 0.999;
                if (debug) std::cout << "BOUNCE : X\n";
            }
        }


        if (((y_pos + diameter + 1) <= 64 && (y_pos - 1) >= 0)) {
            if ((Object::frame[x_pos + cur][y_pos - 1] &&
                 Object::frame[x_pos + cur][y_pos - 1]->getType() == WALL) or
                (Object::frame[x_pos + cur][y_pos + diameter + 1] &&
                 Object::frame[x_pos + cur][y_pos + diameter + 1]->getType() == WALL)) {
                marple->y_velocity *= -1;
//                marple->y_velocity *= 0.999;
                if (debug) std::cout << "BOUNCE : Y\n";
            }
        }
    }
}




/*
*pass in marple object
*get current velocity
*read current angle - > acceleration
*100 -> -100 : (1p/s)/s -> -1p/s/s
*apply the acceleration
*position + (velocity + acceleration) = new position

*once new position obtained, check for collisions
*if in new position there is a wall
*check if marple new position would touch wall or be inside wall
*if inside wall, reposition, so it only touches wall
*if touching wall invert the acceleration so it "bounces off" wall
*check if marple new position would touch hole
*if touches hole, set new position to start position to teleport it back to the start.
*/
