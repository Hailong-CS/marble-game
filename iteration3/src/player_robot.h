/**
 * @file player_robot.h
 *
 * @copyright 2017 3081 Hailong Zeng, All rights reserved.
 */

#ifndef SRC_PLAYER_ROBOT_H_
#define SRC_PLAYER_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
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
/**
 * @brief Player robot will be controled by user. User can turn the robot to
 * right or left, and speed up or slow down. It will collide with entities. It
 * will freeze the autobot, or be freezed by the superbot. It also has battery,
 * so that the user has to collide with recharge station in a certain amount of
 * time. 
 */

class PlayerRobot : public Robot {
 public:
  explicit PlayerRobot(const struct player_robot_params* const params);

  void TimestepUpdate(unsigned int dt);
  void Reset();

  void Accept(EventRecharge * e);
  void Accept(EventCollision * e);

  void EventCmd(enum event_commands cmd);

  double max_battery_level(void) { return battery_.get_max(); }

  double get_battery_level(void) { return battery_.get_level(); }
  void set_battery_level(double db) {battery_.set_level(db);}

  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle();
  }
  void set_heading_angle(double ha) {
    motion_handler_.set_heading_angle(ha);
  }

  double get_speed(void) { return motion_handler_.get_speed(); }
  void set_speed(double sp) { motion_handler_.set_speed(sp); }

  std::string name(void) const {
    return "PlayerRobot";
  }

  char get_type(void) { return 'P'; }

 private:
  int cnt;
  double heading_angle_;
  double angle_delta_;
  RobotBattery battery_;
  RobotMotionHandler motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  // position and speed are for restart purpose
  Position ini_pos_;
  double speed_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_PLAYER_ROBOT_H_ */
