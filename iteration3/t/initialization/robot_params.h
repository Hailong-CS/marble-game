/**
 * @file robot_params.h
 *
 * @copyright 2017 3081 Hailong Zeng, All rights reserved.
 */

#ifndef ROBOT_PARAMS_H_
#define ROBOT_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "arena_mobile_entity_params.h"



/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct robot_params : public arena_mobile_entity_params {
	robot_params(void) :
		arena_mobile_entity_params(),
		heading_angle(),
		speed() {}
		
	double heading_angle;
	double speed;
};


#endif /* ROBOT_PARAMS_H_ */
