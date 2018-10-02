/**
 * @file player_robot_params.h
 *
 * @copyright 2017 3081 staff and Hailong Zeng, All rights reserved.
 */

#ifndef SRC_PLAYER_ROBOT_PARAMS_H_
#define SRC_PLAYER_ROBOT_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct player_robot_params : public robot_params {
   player_robot_params(void) :
      robot_params(),
      battery_max_charge(),
      angle_delta() {}

   double battery_max_charge;
   uint angle_delta;
};

NAMESPACE_END(csci3081);

#endif /* SRC_PLAYER_ROBOT_PARAMS_H_ */
