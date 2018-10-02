/**
 * @file arena_params.h
 *
 * @copyright 2017 3081 Staff and Hailong Zeng, All rights reserved.
 *
 */

#ifndef SRC_ARENA_PARAMS_H_
#define SRC_ARENA_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity_params.h"
#include "src/robot_params.h"
#include "src/player_robot_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
#define MAX_OBSTACLES 8
#define MAX_AUTOBOT 8

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct arena_params {
	struct player_robot_params robot;
	struct robot_params home_base;
	struct robot_params autobot[MAX_AUTOBOT];
	struct arena_entity_params recharge_station;
	struct arena_entity_params obstacles[MAX_OBSTACLES];

	uint x_dim;
	uint y_dim;
	size_t n_autobots;
	size_t n_obstacles;
	double max_speed;
	double max_angle;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_PARAMS_H_ */
