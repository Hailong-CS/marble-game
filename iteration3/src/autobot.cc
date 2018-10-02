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
      s(false),
      id_(-1),
      motion_handler_(),
      motion_behavior_(),
      ini_pos_(params->pos),
      speed_(0),
      sensor_touch_(),
      sensor_proximity_(),
      sensor_entity_type_(),
      sensor_distress_() {
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
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
  if (s == true) {
    set_speed(5);
  }
}

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Autobot::Accept(EventCollision * e) {
  if (e->bound_collided() == true) {
    set_pos(e->point_of_contact());
    e->bound_collided(false);
  }
  if (s == false) {
    if (e->get_type() == 'P') {
      e->get_colliding_type('N');
      set_speed(0);
    } else if (e->get_type() == 'H') {
      e->get_colliding_type('N');
      superbot();
    } else if (e->get_type() == 'A') {
      e->get_colliding_type('N');
      set_speed(7);
    } else if (e->get_type() == 'S') {
      e->get_colliding_type('N');
      set_speed(7);
    } else {
      e->get_colliding_type('N');
      sensor_touch_.Accept(e);
    }
  } else {
    e->get_colliding_type('N');
    sensor_touch_.Accept(e);
  }
}

void Autobot::Accept(EventSensor * e) {
  if (s == false && e->get_type() == 'P') {
    set_heading_angle(get_heading_angle() + 180);
  } else if (e->get_type() == 'A' && e->get_speed() == 0) {
    set_heading_angle(get_heading_angle());
    set_speed(7);
  }
}

void Autobot::superbot() {
  s = true;
  set_color(Color(200, 100, 30, 255));
}

void Autobot::activate() {
  sensor_distress_.activated(true);
}

void Autobot::Reset() {
  set_heading_angle(heading_angle_);
  set_pos(ini_pos_);
  set_speed(speed_);
  motion_handler_.Reset();
  sensor_touch_.Reset();
  sensor_proximity_.Reset();
  sensor_distress_.Reset();
} /* Reset() */

NAMESPACE_END(csci3081);
