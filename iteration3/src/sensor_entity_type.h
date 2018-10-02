/**
 * @file sensor_entity_type.h
 *
 * @copyright 2017 Hailong Zeng, All rights reserved.
 */

#ifndef SRC_SENSOR_ENTITY_TYPE_H
#define SRC_SENSOR_ENTITY_TYPE_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>
#include <string>

#include "src/position.h"
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
class SensorEntityType {
   public:
      SensorEntityType() : activated_(false), type_('N') {}
      ~SensorEntityType() {}

      char get_type(void) const { return type_; }
      void set_type(char t) { type_ = t; }

      bool get_activated(void) const { return activated_; }
      void set_activated(bool a) { activated_ = a;}

      void Accept(EventCollision * e) {
         if (e->collided()) {
            activated_ = true;
         } else {
            activated_ = false;
         }
      }
      

      void Reset(void) { activated_ = false; }

   private:
      bool activated_;
      char type_;
};

NAMESPACE_END(csci3081);

#endif   /* SRC_SENSOR_ENTITY_TYPE_H */
