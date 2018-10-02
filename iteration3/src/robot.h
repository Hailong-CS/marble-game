/**
 * @file robot.h
 *
 * @copyright 2017 3081 Hailong Zeng, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/arena_mobile_entity.h"
#include "src/config.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Robot : public ArenaMobileEntity {
   public:
      explicit Robot(double radius, double collision_delta,
                const Position& pos, const Color& color,
                double max_speed_, double max_angle_) :
               ArenaMobileEntity(radius, collision_delta, pos, color),
               max_speed_(),
               max_angle_() {};
      
      virtual std::string name(void) const = 0;
      
      double get_max_speed(void) const { return max_speed_; }

   private:
      double max_speed_;
      double max_angle_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ROBOT_H_ */