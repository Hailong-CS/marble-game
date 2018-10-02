/**
 * @file robot_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include "src/robot_battery.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

/* previous code
double RobotBattery::Deplete(__unused Position old_pos,
  __unused Position new_pos, __unused double dt) {
  // @todo deplete battery by some value based on movement and speed
  return charge_;
} *//* deplete() */

double RobotBattery::Deplete(__unused Position old_pos,
   __unused Position new_pos, __unused double dt) {
    int dfrc_x, dfrc_y;
    double dfrc_ds, dfrc_angle;
    dfrc_x = new_pos.x - old_pos.x;
    dfrc_y = new_pos.y - old_pos.y;
    dfrc_ds = sqrt(pow(dfrc_x, 2)+pow(dfrc_y, 2));
    if (dfrc_ds == 0) {
        dfrc_angle = 0;
    } else {
        dfrc_angle = asin(dfrc_y/dfrc_ds) * M_PI / 180;
    }

    charge_ = charge_ - (dfrc_ds * kLINEAR_SCALE_FACTOR
            + dfrc_angle * kANGULAR_SCALE_FACTOR  + kBASE_DEPLETION) * dt;

    if (charge_ < 0) {
        charge_ = 0;
    }

    return charge_;
}

void Accept(__unused EventCollision * e) {
  /* @todo deplete battery by some value -- arbitrary selected for bumping */
}

NAMESPACE_END(csci3081);
