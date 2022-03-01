
#include "dynamics.h"
#include "../graphics/gfx.h"
#include <iostream>
#include "MPU6050.h"

void updateMarple(Marple* marple, MPU6050* gyro) {
    float x, y, z;
    float weighting_factor = 0.002;
    float x_pos = marple->getPos()[0], y_pos = marple->getPos()[1];
    gyro->getGyro(&x, &y, &z);
    marple->x_velocity += (x * weighting_factor);
    marple->y_velocity += (y * weighting_factor);
    marple->move(marple->x_velocity, marple->y_velocity);

    std::cout << "\npos: " << x_pos << ", " << y_pos << "\n";
    std::cout << "gyro: " << x << ", " << y << "\n";
}

/*pass in marple object
 * get current velocity
 * read current angle - > acceleration
 *          100 -> -100 : (1p/s)/s -> -1p/s/s
 * apply the acceleration
 *          position + (velocity + acceleration) = new position

 once new position obtained, check for collisions
    *if in new position there is a wall
        *check if marple new position would touch wall or be inside wall
            *if inside wall, reposition so it only touches wall
            *if touching wall invert the acceleration so it "bounces off" wall
        *check if marple new position would touch hole
            *if touches hole, set new psotion to start position to teleport it back to the start.
            */
