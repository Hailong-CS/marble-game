/**
 * @file sensor_base.h
 *
 * @copyright 2017 Hailong Zeng, All rights reserved.
 */

#ifndef SRC_SENSOR_BASE_H_
#define SRC_SENSOR_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class SensorBase{
 public:
  SensorBase() : activated_(false) {}
  virtual ~SensorBase() {}
  /**
   * @brief Get the current activation reading from the sensor.
   */
  bool activated(void) const { return activated_; };
  void activated(bool value) { activated_ = value; };

  virtual void Accept(EventCollision * e) = 0;

  virtual void Reset(void) = 0;

 private:
 	bool activated_;
};

NAMESPACE_END(csci3081);

#endif   /* SRC_SENSOR_BASE_H_ */
