/**
 * @file config.h
 *
 * @copyright 2017 Hailong Zeng, All rights reserved.
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cstdlib>
#include "common.h"
#include "arena_params.h"
#include "robot_params.h"
#include "position.h"
#include "color.h"


class Config {
	public:
	 // constructor
	 Config();

	 void parser(int const argc, char* const argv[],
	 			 arena_params& aparams, player_robot_params& prparams);

	 void basic_set(std::string line, arena_params& aparams);
	 void player_robot(std::string line, player_robot_params& prparams);

	private:
	 double pos_x;
	 double pos_y;

	 int c_0;
	 int c_1;
	 int c_2;
	 int c_3;
};


#endif // SRC_CONFIG_H_