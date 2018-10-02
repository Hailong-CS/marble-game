/**
 * @file player_robot.cc
 *
 * @copyright 2017 3081 Hailong Zeng, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player_robot.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
PlayerRobot::PlayerRobot(const struct player_robot_params* const params) :
  Robot(params->radius, params->collision_delta,
                    params->pos, params->color, 15.0, 360.0),
  battery_(params->battery_max_charge),
  angle_delta_(params->angle_delta),
  ini_pos_(params->pos),
  heading_angle_(0),
  speed_(0),
  cnt(0),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_() {
    motion_handler_.set_heading_angle(38);
    motion_handler_.set_speed(3);
    motion_handler_.set_angle_delta(params->angle_delta);
    motion_handler_.set_max_speed(15);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void PlayerRobot::TimestepUpdate(uint dt) {
  Position old_pos = get_pos();
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
  // Deplete battery as appropriate given distance and speed of movement
  battery_.Deplete(old_pos, get_pos(), dt);
  if (get_speed() == 0) {
    cnt += dt;
    if (cnt == 15) {
      set_speed(8);
      cnt = 0;
    }
  }
} /* TimestepUpdate() */

void PlayerRobot::Accept(__unused EventRecharge * e) {
  battery_.EventRecharge();
}

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void PlayerRobot::Accept(EventCollision * e) {
  if (e->bound_collided() == true) {
    set_pos(e->point_of_contact());
    e->bound_collided(false);
  }
  if (e->get_type() == 'S') {
    set_speed(0);
    e->get_colliding_type('N');
  }
  sensor_touch_.Accept(e);
}

// User input commands to change heading or speed
void PlayerRobot::EventCmd(enum event_commands cmd) {
  motion_handler_.AcceptCommand(cmd);
} /* event_cmd() */

void PlayerRobot::Reset() {
  set_heading_angle(heading_angle_);
  set_pos(ini_pos_);
  set_speed(speed_);
  battery_.Reset();
  motion_handler_.Reset();
  sensor_touch_.Reset();
} /* Reset() */



NAMESPACE_END(csci3081);
