#pragma once

#ifndef MARPLE_TILT_DYNAMICS_H
#define MARPLE_TILT_DYNAMICS_H

#endif //MARPLE_TILT_DYNAMICS_H

#include <iostream>

class MPU6050;
class Marple;

void updateMarple(Marple *marple, MPU6050 *gyro, volatile float x, volatile float y, volatile float z, bool debug = false, float bounce_loss = 0.75);

void handleCollision(Marple *marple, bool debug=false);