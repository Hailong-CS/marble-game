/**
 * @file robot_motion_behavior.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_behavior.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RobotMotionBehavior::UpdatePosition(ArenaMobileEntity * const ent,
                                       unsigned int dt) {
  //Position old_pos = ent->get_pos();
  Position new_pos = ent->get_pos();

  // Movement is always along the heading_angle (i.e. the hypotenuse)
  new_pos.x += cos(ent->get_heading_angle()*M_PI/180.0)*ent->get_speed()*dt;
  new_pos.y += sin(ent->get_heading_angle()*M_PI/180.0)*ent->get_speed()*dt;
  ent->set_pos(new_pos);
  // print the location of robot and homebase
  /*
  printf(
      "Updated %s kinematics: old_pos=(%lf, %lf), new_pos=(%lf, %lf)\n",
      ent->name().c_str(), old_pos.x, old_pos.y, new_pos.x, new_pos.y);*/
} /* update_position() */

NAMESPACE_END(csci3081);
