/**
 * @file arena_params.h
 *
 * @copyright 2017 3081 Staff and Hailong Zeng, All rights reserved.
 *
 */

#ifndef ARENA_PARAMS_H_
#define ARENA_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "arena_entity_params.h"
#include "robot_params.h"
#include "player_robot_params.h"

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

#endif /* ARENA_PARAMS_H_ */
