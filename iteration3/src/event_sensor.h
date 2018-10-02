/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Hailong Zeng, All rights reserved.
 */

#ifndef SRC_EVENT_SENSOR_H
#define SRC_EVENT_SENSOR_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class EventSensor : public EventBaseClass {
 public:
  EventSensor() : collided_(false), position_(0, 0), 
                  heading_angle_(0), type('N'), speed_(0) {}
  void EmitMessage(void) {}
  bool collided() { return collided_; }
  void collided(bool c) { collided_ = c; }

  Position position() { return position_; }
  void position(Position p) { position_ = p; }

  double heading_angle() { return heading_angle_; }
  void heading_angle(double aoc) { heading_angle_ = aoc; }

  void get_colliding_type(char c) { type = c; }
  char get_type(void) { return type;}

  void get_colliding_speed(double s) { speed_ = s;}
  double get_speed(void) { return speed_;}

 private:
  bool collided_;
  Position position_;
  double heading_angle_;
  char type;
  double speed_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_SENSOR_H */
