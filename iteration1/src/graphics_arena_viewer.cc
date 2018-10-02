 /**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include <iostream>
#include <string>
#include <vector>

#include "src/robot.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/arena_params.h"
#include "src/event_keypress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer
  (const struct arena_params* const params)
    : csci3081::GraphicsApp(params->x_dim, params->y_dim, "Robot Simulation"),
      arena_(new Arena(params)),
      paused_(false),
      pause_btn_(nullptr),
      last_dt(0) {
  nanogui::FormHelper *gui = new nanogui::FormHelper(this);
  nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10),
                                                        "Menu");
  gui->addGroup("Simulation Control");

  gui->addButton("Restart",
                  std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  pause_btn_ = gui->addButton("Pause",
                    std::bind(&GraphicsArenaViewer::OnPauseBtnPressed, this));

  gui->addGroup("Robot stats");
  robot_battery_ = new nanogui::ProgressBar(window);
  robot_battery_->setFixedWidth(50);
  robot_battery_->setValue(1);
  gui->addWidget("Robot Battery", robot_battery_);
  robot_pos_x_ = new nanogui::IntBox<int>(window);
  robot_pos_y_ = new nanogui::IntBox<int>(window);
  robot_speed_ = new nanogui::IntBox<int>(window);
  robot_angle_ = new nanogui::IntBox<int>(window);
  robot_battery_text_ = new nanogui::IntBox<int>(window);
  robot_pos_x_->setFixedWidth(50);
  robot_pos_y_->setFixedWidth(50);
  robot_speed_->setFixedWidth(50);
  robot_angle_->setFixedWidth(50);
  robot_battery_text_->setFixedWidth(50);
  robot_pos_x_->setEditable(false);
  robot_pos_y_->setEditable(false);
  robot_speed_->setEditable(false);
  robot_angle_->setEditable(false);
  robot_battery_text_->setEditable(false);
  robot_pos_x_->setAlignment(nanogui::TextBox::Alignment::Center);
  robot_pos_y_->setAlignment(nanogui::TextBox::Alignment::Center);
  robot_speed_->setAlignment(nanogui::TextBox::Alignment::Center);
  robot_angle_->setAlignment(nanogui::TextBox::Alignment::Center);
  robot_battery_text_->setAlignment(nanogui::TextBox::Alignment::Center);
  gui->addWidget("Robot.x", robot_pos_x_);
  gui->addWidget("Robot.y", robot_pos_y_);
  gui->addWidget("Robot.speed", robot_speed_);
  gui->addWidget("Robot.angle", robot_angle_);
  gui->addWidget("Robot.battery", robot_battery_text_);

  gui->addGroup("HomeBase stats");
  home_pos_x_ = new nanogui::IntBox<int>(window);
  home_pos_y_ = new nanogui::IntBox<int>(window);
  home_speed_ = new nanogui::IntBox<int>(window);
  home_angle_ = new nanogui::IntBox<int>(window);
  home_pos_x_->setEditable(false);
  home_pos_y_->setEditable(false);
  home_speed_->setEditable(false);
  home_angle_->setEditable(false);
  home_pos_x_->setFixedWidth(50);
  home_pos_y_->setFixedWidth(50);
  home_speed_->setFixedWidth(50);
  home_angle_->setFixedWidth(50);
  home_pos_x_->setAlignment(nanogui::TextBox::Alignment::Center);
  home_pos_y_->setAlignment(nanogui::TextBox::Alignment::Center);
  home_speed_->setAlignment(nanogui::TextBox::Alignment::Center);
  home_angle_->setAlignment(nanogui::TextBox::Alignment::Center);
  gui->addWidget("HomeBase.x", home_pos_x_);
  gui->addWidget("HomeBase.y", home_pos_y_);
  gui->addWidget("HomeBase.speed", home_speed_);
  gui->addWidget("HomeBase.angle", home_angle_);

  performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (arena_->paused_game == true) {
    paused_ = arena_->paused_game;
  }
  if (!paused_) {
    last_dt += dt;
    while (last_dt > 0.05) {
      arena_->AdvanceTime();
      last_dt -= 0.05;



      robot_pos_x_->setValue(
          static_cast<int>(arena_->robot()->get_pos().x));
      robot_pos_y_->setValue(
          static_cast<int>(arena_->robot()->get_pos().y));
      robot_speed_->setValue(
          static_cast<int>(arena_->robot()->get_speed()));
      robot_angle_->setValue(
          static_cast<int>(arena_->robot()->get_heading_angle()));
      robot_battery_text_->setValue(
          static_cast<int>(arena_->robot()->get_battery_level()));
      home_pos_x_->setValue(
          static_cast<int>(arena_->home_base()->get_pos().x));
      home_pos_y_->setValue(
          static_cast<int>(arena_->home_base()->get_pos().y));
      home_speed_->setValue(
          static_cast<int>(arena_->home_base()->get_speed()));
      home_angle_->setValue(
          static_cast<int>(arena_->home_base()->get_heading_angle()));
      robot_battery_->setValue(
          static_cast<float>(
              arena_->robot()->get_battery_level() /
                  arena_->robot()->max_battery_level()));
    }
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnRestartBtnPressed() {
  arena_->Reset();
}

void GraphicsArenaViewer::OnPauseBtnPressed() {
  if (arena_->paused_game == true) {
    paused_ = arena_->paused_game;
  } else {
    paused_ = !paused_;
  }
  if (paused_) {
    pause_btn_->setCaption("Play");
  } else {
    pause_btn_->setCaption("Pause");
  }
}

void GraphicsArenaViewer::OnMouseMove(int x, int y) {
  std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseDown(int x, int y) {
  std::cout << "Left mouse button DOWN (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseUp(int x, int y) {
  std::cout << "Left mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnRightMouseDown(int x, int y) {
  std::cout << "Right mouse button DOWN (" << x << ", " << y << ")\n";
}

void GraphicsArenaViewer::OnRightMouseUp(int x, int y) {
  std::cout << "Right mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnKeyDown(const char *c, int modifiers) {
  std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnKeyUp(const char *c, int modifiers) {
  std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyDown(int key, int scancode,
  int modifiers) {
  EventKeypress e(key);
  arena_->Accept(&e);
  std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyUp(int key, int scancode, int modifiers) {
  std::cout << "Special Key UP key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx, const Robot* const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading for this robot
  nvgSave(ctx);
  nvgTranslate(ctx, robot->get_pos().x, robot->get_pos().y);
  nvgRotate(ctx, robot->get_heading_angle());

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, robot->get_radius());
  nvgFillColor(ctx, nvgRGBA(robot->get_color().r,
                            robot->get_color().g,
                            robot->get_color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, M_PI / 2.0);
  // nvgRotate(ctx, robot->heading_angle());
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, robot->name().c_str(), NULL);
  nvgRestore(ctx);
  nvgRestore(ctx);
/*
  // adding a lab for showing the battary level
  nvgSave(ctx);
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, battery_level.c_str(), NULL);
  nvgRestore(ctx);
  nvgRestore(ctx);*/
}

void GraphicsArenaViewer::DrawObstacle(NVGcontext *ctx,
                                       const Obstacle* const obstacle) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
    obstacle->get_radius());
  nvgFillColor(ctx, nvgRGBA(obstacle->get_color().r,
                            obstacle->get_color().g,
                            obstacle->get_color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
          obstacle->name().c_str(), NULL);
}

void GraphicsArenaViewer::DrawHomeBase(NVGcontext *ctx,
                               const HomeBase* const home) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, home->get_pos().x, home->get_pos().y, home->get_radius());
  nvgFillColor(ctx, nvgRGBA(home->get_color().r,
                            home->get_color().g,
                            home->get_color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, home->get_pos().x, home->get_pos().y, home->name().c_str(),
    NULL);
}

// This is the primary driver for drawing all entities in the arena.
// It is called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  std::vector<Obstacle*> obstacles = arena_->obstacles();
  for (size_t i = 0; i < obstacles.size(); i++) {
    DrawObstacle(ctx, obstacles[i]);
  } /* for(i..) */

  DrawRobot(ctx, arena_->robot());
  DrawHomeBase(ctx, arena_->home_base());
}

NAMESPACE_END(csci3081);
