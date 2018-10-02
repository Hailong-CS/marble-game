/**
 * @file home_base.cc
 * @copyright 2017 Hailong Zeng reserved
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/home_base.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);


/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

HomeBase::HomeBase(const struct robot_params* const params) :
    Robot(params->radius, 1, params->pos, params->color, 15, 360),
    collision_delta_(1),
    heading_angle_(0),
    motion_handler_(),
    motion_behavior_(),
    sensor_touch_() {
        int rand_heading_angle = rand() % 360 - 180;
        int rand_speed = (rand() %
        static_cast <int> (motion_handler_.get_max_speed() - 3)) + 3;
        set_heading_angle(rand_heading_angle);
        set_speed(rand_speed);
    }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void HomeBase::TimestepUpdate(uint dt) {
    Position old_pos = get_pos();
    motion_handler_.UpdateVelocity(sensor_touch_);
    motion_behavior_.UpdatePosition(this, dt);
    int rand1 = rand() % 100;
    int rand2 = rand() % 100;
    if (rand1 == rand2) {
        int rand_heading_angle = rand() % 360 - 180;
        set_heading_angle(rand_heading_angle);
        set_speed(7);
    }
}

void HomeBase::Reset() {
    int rand_heading_angle = rand() % 360 - 180;
    set_pos(Position(400, 400));
    set_heading_angle(rand_heading_angle);
    motion_handler_.Reset();
    sensor_touch_.Reset();
}

void HomeBase::Accept(EventCollision * e) {
    sensor_touch_.Accept(e);
}

NAMESPACE_END(csci3081);

