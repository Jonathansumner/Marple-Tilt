#ifndef MARPLE_TILT_DYNAMICS_H
#define MARPLE_TILT_DYNAMICS_H

#endif //MARPLE_TILT_DYNAMICS_H

#include "gfx.h"
#include "MPU6050.h"
#include <iostream>

void updateMarple(Marple *marple, MPU6050 *gyro, bool debug = false, float bounce_loss = 0.75);

void handleCollision(Marple *marple, bool debug=false);