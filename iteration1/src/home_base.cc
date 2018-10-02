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

HomeBase::HomeBase(const struct home_base_params* const params) :
    ArenaMobileEntity(params->radius, 1, params->pos, params->color),
    collision_delta_(1),
    heading_angle_(0),
    motion_handler_(),
    motion_behavior_(),
    sensor_touch_() {
        int rand_ha = rand() % 360 - 180;
        int rand_speed = rand() %
        static_cast <int> (motion_handler_.get_max_speed());
        set_heading_angle(rand_ha);
        set_speed(rand_speed);
    }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void HomeBase::TimestepUpdate(uint dt) {
    motion_handler_.UpdateVandA(sensor_touch_);
    motion_behavior_.UpdatePosition(this, dt);
    int rand1 = rand() % 100;
    int rand2 = rand() % 100;
    if (rand1 == rand2) {
        int rand_ha = rand() % 360 - 180;
        set_heading_angle(rand_ha);
    }
}

void HomeBase::Reset() {
    int rand_ha = rand() % 360 - 180;
    set_pos(Position(400, 400));
    set_heading_angle(rand_ha);
    motion_handler_.Reset();
    sensor_touch_.Reset();
}

void HomeBase::Accept(EventCollision * e) {
    if (e->bound_collided() == true) {
        set_pos(e->point_of_contact());
        e->bound_collided(false);
    }
    sensor_touch_.Accept(e);
}

NAMESPACE_END(csci3081);

