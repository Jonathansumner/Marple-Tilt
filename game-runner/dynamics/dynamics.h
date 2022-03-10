
#ifndef MARPLE_TILT_DYNAMICS_H
#define MARPLE_TILT_DYNAMICS_H

#endif //MARPLE_TILT_DYNAMICS_H

#include "../graphics/gfx.h"
#include "MPU6050.h"

void updateMarple(Marple *marple, MPU6050* gyro, const vector <bool>& debug = {false, false});

void handleCollision(Marple *marple, bool debug=false);