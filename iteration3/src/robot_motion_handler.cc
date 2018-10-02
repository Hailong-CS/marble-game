/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_handler.h"
#include "cmath"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotMotionHandler::RobotMotionHandler() :
  heading_angle_(0),
  speed_(0),
  max_speed_(15),
  max_angle_(360) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void RobotMotionHandler::AcceptCommand(enum event_commands cmd) {
  switch (cmd) {
  case COM_TURN_LEFT:
    heading_angle_ -= angle_delta_;
    if (heading_angle_ < 0) { heading_angle_ += max_angle_; }
    break;
  case COM_TURN_RIGHT:
    heading_angle_ += angle_delta_;
    if (heading_angle_ > max_angle_) { heading_angle_ -= max_angle_; }
    break;
  case COM_SPEED_UP:
    if (speed_ < max_speed_) {
      speed_++;
    } else {
      speed_ = max_speed_;
    }
    break;
  case COM_SLOW_DOWN:
    if (speed_ > 0) {
      speed_--;
    } else {
      speed_ = 0;
    }
    break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  }

/*
void RobotMotionHandler::AcceptCommand(enum event_commands cmd) {
  switch (cmd) {
  case COM_TURN_LEFT: break;
  case COM_TURN_RIGHT: break;
  case COM_SPEED_UP: break;
  case COM_SLOW_DOWN: break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  }  //switch()*/
}
/* accept_command() */

void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    heading_angle_ = - st.angle_of_contact();
    speed_ *= 0.9;
    st.Reset();
  }
}


NAMESPACE_END(csci3081);
