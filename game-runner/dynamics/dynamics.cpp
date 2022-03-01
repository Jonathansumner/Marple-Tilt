//
// Created by Jonat on 01/03/2022.
//

#include "dynamics.h"

void updateMarple(Marple marple) {

}

/*pass in marple object
 * get current velocity
 * read current angle - > acceleration
 *          100 -> -100 : (1p/s)/s -> -1p/s/s
 * apply the acceleration
 *          position + (velocity + acceleration) = new position
 */

/*once new position obtained, check for collisions
    *if in new position there is a wall
        *check if marple new position would touch wall or be inside wall
            *if inside wall, reposition so it only touches wall
            *if touching wall invert the acceleration so it "bounces off" wall
        *check if marple new position would touch hole
            *if touches hole, set new psotion to start position to teleport it back to the start.