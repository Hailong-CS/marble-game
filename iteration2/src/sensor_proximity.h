/**
 * @file sensor_proximity.h
 *
 * @copyright 2017 Hailong Zeng, All rights reserved.
 */

#ifndef SRC_SENSOR_PROXIMITY_H
#define SRC_SENSOR_PROXIMITY_H

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
class SensorProximity : public SensorBase {
   public:
      SensorProximity() : length_(0), range_(0), dist(0) {}
      ~SensorProximity() {}

      double get_length(void) const { return length_; }
      void set_length(double l) { length_ = l; }

      double get_range(void) const { return range_; }
      void set_range(double r) { range_ = r; }

      void Accept(EventCollision * e) {
         if (e->collided()) {
            activated(true);
         } else {
            activated(false);
         }
      }

      void Reset(void) { activated(false); }

   private:
      // length and range will be the view cone emanated from the center of entity
      double length_;
      double range_;
      double dist;
};

NAMESPACE_END(csci3081);

#endif   /* SRC_SENSOR_PROXIMITY_H */
