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
    int x_dist, y_dist;
    double plan_dist, angle_difference;
    x_dist = new_pos.x - old_pos.x;
    y_dist = new_pos.y - old_pos.y;
    plan_dist = sqrt(pow(x_dist, 2)+pow(y_dist, 2));
    if (plan_dist == 0) {
        angle_difference = 0;
    } else {
        angle_difference = asin(y_dist/plan_dist) * M_PI / 180;
    }

    charge_ = charge_ - (plan_dist * kLINEAR_SCALE_FACTOR
          + angle_difference * kANGULAR_SCALE_FACTOR  + kBASE_DEPLETION) * dt;

    if (charge_ < 0) {
        charge_ = 0;
    }

    return charge_;
}

void Accept(__unused EventCollision * e) {
  /* @todo deplete battery by some value -- arbitrary selected for bumping */
}

NAMESPACE_END(csci3081);
