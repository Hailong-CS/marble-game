/**
 * @file sensor_distress.h
 *
 * @copyright 2017 Hailong Zeng, All rights reserved.
 */

#ifndef SRC_SENSOR_DISTRESS_H
#define SRC_SENSOR_DISTRESS_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/position.h"
#include "src/sensor_base.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 *
 */
class SensorDistress : public SensorBase {
   public:
      SensorDistress() : count_(0), range_(0) {}
      ~SensorDistress() {}

      double get_count(void) const { return count_; }
      void set_count(double c) { count_ = c; }

      double get_range(void) const { return range_; }
      void set_range(double r) { range_ = r; }
      

      void Reset(void) { activated(false); }

   private:
      int count_;
      double range_;
};

NAMESPACE_END(csci3081);

#endif   /* SRC_SENSOR_DISTRESS_H */
