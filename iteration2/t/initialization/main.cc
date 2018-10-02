#include <iostream>
#include "config.h"
#include "arena_params.h"
#include "player_robot_params.h"

using namespace std;

int main(int argc, char* argv[]){
	// get argument counts and argument, which is filename here
	argc--;
	argv++;
	Config file;

	player_robot_params prparams;
	arena_params aparams;

	file.parser(argc, argv, aparams, prparams);

	cout << aparams.x_dim << endl;
	cout << aparams.y_dim << endl;

	//file.display(aparams, rparams);

	return 0;
}