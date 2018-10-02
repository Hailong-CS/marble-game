/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cstdlib>
#include <ctime>

#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/robot_params.h"
#include "src/color.h"
#include "src/position.h"
#include "src/config.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char* argv[]) {
  // random seed
  srand(time(NULL));
  // get argument counts and argument, which is filename here
  argc--;
  argv++;

  // Essential call to initiate the graphics window
  csci3081::InitGraphics();

  // Initialize default start values for various arena entities
  csci3081::player_robot_params prparams;

  csci3081::arena_params aparams;

  csci3081::Config file;

  file.parser(argc, argv, aparams, prparams);

  // Start up the graphics (which creates the arena).
  // Run will enter the nanogui::mainloop()
  csci3081::GraphicsArenaViewer *app =
    new csci3081::GraphicsArenaViewer(&aparams);
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
