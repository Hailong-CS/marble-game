/**
 * @file autobot.h
 *
 * @copyright 2017 3081 Staff and Hailong Zeng, All rights reserved.
 */

#ifndef SRC_AUTOBOT_H
#define SRC_AUTOBOT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/sensor_proximity.h"
#include "src/sensor_entity_type.h"
#include "src/sensor_distress.h" 
#include "src/robot_battery.h"
#include "src/robot.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/config.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Autobot : public Robot {
   public:
      explicit Autobot(const struct robot_params* const params);

      void TimestepUpdate(unsigned int dt);
      void Reset();

      void Accept(EventCollision * e);

      double get_heading_angle(void) const {
       return motion_handler_.get_heading_angle();
      }
      void set_heading_angle(double ha) {
       motion_handler_.set_heading_angle(ha);
      }

      double get_speed(void) { return motion_handler_.get_speed(); }
      void set_speed(double sp) { motion_handler_.set_speed(sp); }

      double collision_delta(void) const { return collision_delta_; }

      int get_id(void) const { return id_; }
      std::string name(void) const {
       return "Autobot" + std::to_string(get_id());
      }

      char get_type(void) { return 'A'; }

   private:
   static unsigned int next_id_;

   int id_;
   double heading_angle_;
   double collision_delta_;
   RobotMotionHandler motion_handler_;
   RobotMotionBehavior motion_behavior_;
   // position and speed are for restart purpose
   Position ini_pos_;
   double speed_;

   SensorTouch sensor_touch_;
   SensorProximity sensor_proximity_;
   SensorEntityType sensor_entity_type_;
   SensorDistress sensor_distress_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_AUTOBOT_H */