/**
 * @file player_robot_params.h
 *
 * @copyright 2017 3081 staff and Hailong Zeng, All rights reserved.
 */

#ifndef PLAYER_ROBOT_PARAMS_H_
#define PLAYER_ROBOT_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "arena_mobile_entity_params.h"


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


#endif /* PLAYER_ROBOT_PARAMS_H_ */
