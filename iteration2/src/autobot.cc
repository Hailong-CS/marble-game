/**
 * @file autobot.cc
 *
 * @copyright 2017 3081 Staff and Hailong Zeng, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/autobot.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Autobot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Autobot::Autobot(const struct robot_params* const params) :
   Robot(params->radius, 1, params->pos, params->color, 15, 360),
      collision_delta_(1),
      heading_angle_(0),
      ini_pos_(params->pos),
      motion_handler_(),
      motion_behavior_(),
      sensor_touch_(),
      id_(-1) {
        int rand_ha = rand() % 360 - 180;
        int rand_speed = (rand() %
        static_cast <int> (motion_handler_.get_max_speed() - 3)) + 3;
        set_heading_angle(rand_ha);
        set_speed(rand_speed);
        id_ = next_id_++;
   }


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Autobot::TimestepUpdate(uint dt) {
  Position old_pos = get_pos();
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
}

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Autobot::Accept(EventCollision * e) {
  if(e->get_type() == 'P') {
    e->get_colliding_type('N');
    set_speed(0);
  } else if (e->get_type() == 'H') {
    e->get_colliding_type('N');
    sensor_touch_.Accept(e);
  } else if (e->get_type() == 'A') {
    e->get_colliding_type('N');
    set_speed(5);
  } else {
    e->get_colliding_type('N');
    sensor_touch_.Accept(e);
  }
}

void Autobot::Reset() {
  set_heading_angle(heading_angle_);
  set_pos(ini_pos_);
  set_speed(speed_);
  motion_handler_.Reset();
  sensor_touch_.Reset();
} /* Reset() */

NAMESPACE_END(csci3081);
