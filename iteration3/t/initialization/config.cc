/**
 * @file config.cc
 *
 * @copyright 2017 Hailong Zeng, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <assert.h>
#include <sstream>

#include "config.h"

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

Config::Config() : pos_x(0), pos_y(0), c_0(0), c_1(0), c_2(0), c_3(0) {}

void Config::parser(int const argc, char* const argv[],
			   	arena_params& aparams, player_robot_params& prparams){

	if (argc != 1) {
		assert(0);
	}

	std::ifstream file_in;
	file_in.open(*argv);
	assert(file_in.is_open());

	std::string line;
	std::string newline;
	char commend[128];

	while(getline(file_in, line)){

		if (line == "") continue;
		if (line[0] == '#') continue;

		sscanf(line.c_str(), "%s", commend);
		std::string cmd = commend;

		if (cmd == "basic_set:") {
			getline(file_in, line);
			for (int i = 0; i < 5; i++) {
				getline(file_in, newline);
				line = line + "/" + newline;
			}
			basic_set(line, aparams);

			continue;
		} else if (cmd == "player_robot:") {
			getline(file_in, line);
			for (int i = 0; i < 5; i++) {
				getline(file_in, newline);
				line = line + "/" + newline;
			}
			player_robot(line, prparams);

			continue;
		} else if (cmd == "homebase") {
			sscanf(line.c_str(), "homebase %lf %lf %lf %d %d %d %d",
				   &aparams.home_base.radius, &pos_x, &pos_y,
				   &c_0, &c_1, &c_2,&c_3);
			aparams.home_base.pos = Position(pos_x, pos_y);
			aparams.home_base.color = Color(c_0, c_1, c_2, c_3);
			
			continue;
		} else if (cmd == "recharge_station") {
			sscanf(line.c_str(), "recharge_station %lf %lf %lf %d %d %d %d",
				   &aparams.recharge_station.radius, &pos_x, &pos_y,
				   &c_0, &c_1, &c_2,&c_3);
			aparams.recharge_station.pos = Position(pos_x, pos_y);
			aparams.recharge_station.color = Color(c_0, c_1, c_2, c_3);
			
			continue;
		} else if (cmd == "autobot:") {
			for (size_t i = 0; i < aparams.n_autobots; i++) {
				getline(file_in, line);
				std::string str;
				std::stringstream ss;
				ss << i;
				str = ss.str() + ". " + "%lf %lf %lf %d %d %d %d";
				sscanf(line.c_str(), str.c_str(), &aparams.autobot[i].radius,
						 &pos_x, &pos_y, &c_0, &c_1, &c_2, &c_3);
				aparams.autobot[i].pos = Position(pos_x, pos_y);
				aparams.autobot[i].color = Color(c_0, c_1, c_2, c_3);
				
			}
			continue;
		} else if (cmd == "obstacles:") {
			for (size_t i = 0; i < aparams.n_obstacles; i++) {
				getline(file_in, line);
				std::string str;
				std::stringstream ss;
				ss << i;
				str = ss.str() + ". " + "%lf %lf %lf %d %d %d %d";
				sscanf(line.c_str(), str.c_str(), &aparams.obstacles[i].radius,
						 &pos_x, &pos_y, &c_0, &c_1, &c_2, &c_3);
				aparams.obstacles[i].pos = Position(pos_x, pos_y);
				aparams.obstacles[i].color = Color(c_0, c_1, c_2, c_3);
				
			}
			continue;
		}*/ /*else {
			std::cout << "There may be some components missing in the";
			std::cout << "configuration file!" << std::endl;
			assert(0);
		}*/
	}
	aparams.robot = prparams;
}

void Config::basic_set(std::string line, arena_params& aparams) {
	int idx = 0;
	std::string newline;

	while (idx < line.length()){
		idx = line.find("/", 0);
		newline = line.substr(0, idx);
		line = line.substr(idx + 1);

		sscanf(newline.c_str(), "x_dim: %d", &aparams.x_dim);
		sscanf(newline.c_str(), "y_dim: %d", &aparams.y_dim);
		sscanf(newline.c_str(), "n_autobots: %li", &aparams.n_autobots);
		sscanf(newline.c_str(), "n_obstacles: %li", &aparams.n_obstacles);
		sscanf(newline.c_str(), "max_speed: %lf", &aparams.max_speed);
		sscanf(newline.c_str(), "max_angle: %lf", &aparams.max_angle);
	}
}

void Config::player_robot(std::string line, player_robot_params& prparams) {
	int idx = 0;
	std::string newline;

	while (idx < line.length()){
		printf("%s\n", line.c_str());
		idx = line.find("/", 0);
		newline = line.substr(0, idx);
		line = line.substr(idx + 1);
		printf("%s\n", newline.c_str());
		sscanf(newline.c_str(), "max_battery: %lf",
							  &prparams.battery_max_charge);
		sscanf(newline.c_str(), "angle_delta: %d", &prparams.angle_delta);
		sscanf(newline.c_str(), "collision_delta: %lf",
									&prparams.collision_delta);
		sscanf(newline.c_str(), "heading_angle: %lf",
							 &prparams.heading_angle);
		sscanf(newline.c_str(), "speed: %lf", &prparams.speed);
		sscanf(newline.c_str(), "%lf %lf %lf %d %d %d %d",
			   &prparams.radius, &pos_x, &pos_y, &c_0, &c_1, &c_2, &c_3);
		prparams.pos = Position(pos_x, pos_y);
		prparams.color = Color(c_0, c_1, c_2, c_3);
	}
}