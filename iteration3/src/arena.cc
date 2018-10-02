/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena.h"
#include "src/robot.h"
#include "src/autobot.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim),
  y_dim_(params->y_dim),
  robot_(new PlayerRobot(&params->robot)),
  n_robots_(1),
  n_autobots_(params->n_autobots),
  n_obstacles_(params->n_obstacles),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
                                        params->recharge_station.pos,
                                        params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  entities_.push_back(robot_);
  entities_.push_back(home_base_);
  mobile_entities_.push_back(robot_);
  mobile_entities_.push_back(home_base_);
  entities_.push_back(recharge_station_);

  for (size_t i = 0; i < n_autobots_; ++i) {
    autobot_.push_back(new Autobot(&params->autobot[i]));
    entities_.push_back(autobot_[i]);
    mobile_entities_.push_back(autobot_[i]);
  }

  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } // for(i..)
}

Arena::~Arena(void) {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::Reset(void) {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

std::vector<Obstacle*> Arena::obstacles(void) {
  std::vector<Obstacle*> res;
  for (auto ent : entities_) {
    Obstacle* o = dynamic_cast<Obstacle*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

void Arena::AdvanceTime(void) {
  // std::cout << "Advancing simulation time by 1 timestep\n";
  UpdateEntitiesTimestep();
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep(void) {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  } /* for(ent..) */

  /*
   * Next, check if the robot has run out of battery
   */

  if (robot_->get_battery_level() <= 0) {
    std::cout << "YOU LOST!!!!!" << std::endl;
    paused_game = true;
    Reset();
  }



  /*
   * Finally, some pairs of entities may now be close enough to be considered
   * colliding, send collision events as necessary.
   *
   * When something collides with an immobile entity, the immobile entity does
   * not move (duh), so no need to send it a collision event.
   */

  unsigned int s_number = 0;
  unsigned int a_number = 0;
  for (auto ent: autobot_) {
    EventSensor es;
    if (ent->get_type() == 'S') {
      s_number ++;
    } else if (ent->get_speed() == 0) {
      a_number ++;
      for (auto aut: autobot_) {
        if (aut == ent) {
          continue;
        }
        aut->activate();
      }
    }
    if (s_number + a_number == n_autobots_ && paused_game == false) {
      std::cout << "YOU Win!!!!!!" << std::endl;
      paused_game = true;
      Reset();
    } else if (s_number == n_autobots_) {
      std::cout << "YOU LOST!!!!!" << std::endl;
      paused_game = true;
      Reset();
    }
    for (size_t i = 0; i < entities_.size(); ++i) {
      if (entities_[i] == ent) {
        continue;
      }
      CheckForConeView(entities_[i], ent, &es);
      if (es.collided()) {
        es.get_colliding_type(entities_[i]->get_type());
        es.get_colliding_speed(entities_[i]->get_speed());
        ent->Accept(&es);
      }
      ent->Accept(&es);
    }
  }


  for (auto ent : mobile_entities_) {
    // Check if it is out of bounds. If so, use that as point of contact.
    EventCollision ec;
    assert(ent->is_mobile());
    CheckForEntityOutOfBounds(ent, &ec);

    // If not at wall, check if colliding with any other entities (not itself)
    if (!ec.collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec, ent->collision_delta());
        if (ec.collided()) {
          ec.get_colliding_type(entities_[i]->get_type());
          ent->Accept(&ec);
          
          if ((ent == robot_) && (entities_[i] == recharge_station_)) {
            EventRecharge er;
            robot_->Accept(&er);
          }

          break;
        }
      } /* for(i..) */
    } else {
      ec.bound_collided(true);
    }
    ent->Accept(&ec);
  } /* for(ent..) */
} /* UpdateEntities() */

void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
                                      EventCollision * event) {
  if (ent->get_pos().x + ent->get_radius() >= x_dim_) {
    // Right Wall
    event->collided(true);
    event->point_of_contact(Position(x_dim_ - ent->get_radius(),
                                      ent->get_pos().y));
    event->angle_of_contact(ent->get_heading_angle() - 180);
  } else if (ent->get_pos().x - ent->get_radius() <= 0) {
    // Left Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_radius(), ent->get_pos().y));
    event->angle_of_contact(ent->get_heading_angle() - 180);
  } else if (ent->get_pos().y + ent->get_radius() >= y_dim_) {
    // Bottom Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x,
                                      y_dim_ - ent->get_radius()));
    event->angle_of_contact(ent->get_heading_angle());
  } else if (ent->get_pos().y - ent->get_radius() <= 0) {
    // Top Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x, ent->get_radius()));
    event->angle_of_contact(ent->get_heading_angle());
  } else {
    event->collided(false);
  }
} /* entity_out_of_bounds() */

void Arena::CheckForEntityCollision(const ArenaEntity *const ent1,
                                    const ArenaEntity *const ent2,
                                    EventCollision *const event,
                                    double collision_delta) {
  // Note: this assumes circular entities 
  double dist = std::sqrt(
      std::pow(ent2->get_pos().x - ent1->get_pos().x, 2) + 
      std::pow(ent2->get_pos().y - ent1->get_pos().y, 2));
  if (dist > ent1->get_radius() + ent2->get_radius() + collision_delta) {
    event->collided(false);
  } else {
    // Populate the collision event.
    // Collided is true
    // Point of contact is point along perimeter of ent1
    // Angle of contact is angle to that point of contact
    // ref: https://stackoverflow.com/a/1736741
    event->collided(true);

    double angle = std::asin(std::abs(ent2->get_pos().x - ent1->get_pos().x) / dist);

    if ((ent2->get_pos().x - ent1->get_pos().x) > 0) {
      if ((ent2->get_pos().y - ent1->get_pos().y) > 0) {
        // lower right
        event->point_of_contact(
            {
                ent1->get_pos().x + std::sin(angle) * ent1->get_radius(),
                ent1->get_pos().y + std::cos(angle) * ent1->get_radius()
            });
        angle = M_PI_2 - angle;
      } else if ((ent2->get_pos().y - ent1->get_pos().y) < 0) {
        // upper right
        event->point_of_contact(
            {
                ent1->get_pos().x + std::sin(angle) * ent1->get_radius(),
                ent1->get_pos().y - std::cos(angle) * ent1->get_radius()
            });
        angle += (3 * M_PI_2);
      } else {  // if ((ent2->get_pos().y - ent1->get_pos().y) == 0)
        // 0 or 360 deg
        event->point_of_contact(
            {
                ent1->get_pos().x + ent1->get_radius(),
                ent1->get_pos().y
            });
        angle = 0;
      }
    } else if ((ent2->get_pos().x - ent1->get_pos().x) < 0)  {
      if ((ent2->get_pos().y - ent1->get_pos().y) > 0) {
        // lower left
        event->point_of_contact(
            {
                ent1->get_pos().x - std::sin(angle) * ent1->get_radius(),
                ent1->get_pos().y + std::cos(angle) * ent1->get_radius()
            });
        angle += M_PI_2;
      } else if ((ent2->get_pos().y - ent1->get_pos().y) < 0) {
        // upper left
        event->point_of_contact(
            {
                ent1->get_pos().x - std::sin(angle) * ent1->get_radius(),
                ent1->get_pos().y - std::cos(angle) * ent1->get_radius()
            });
        angle = (M_PI_2 * 2) + (M_PI_2 - angle);
      } else {  // if ((ent2->get_pos().y - ent1->get_pos().y) == 0)
        // 180 deg
        event->point_of_contact(
            {
                ent1->get_pos().x - ent1->get_radius(),
                ent1->get_pos().y
            });
        angle = M_PI;
      }
    } else {  // if ((ent2->get_pos().x - ent1->get_pos().x) == 0)
      if ((ent2->get_pos().y - ent1->get_pos().y) > 0) {
        // 90 deg
        event->point_of_contact(
            {
                ent1->get_pos().x,
                ent1->get_pos().y + ent1->get_radius()
            });
        angle = M_PI_2;
      } else if ((ent2->get_pos().y - ent1->get_pos().y) < 0) {
        // 270 deg
        event->point_of_contact(
            {
                ent1->get_pos().x,
                ent1->get_pos().y - ent1->get_radius()
            });
        angle = (3 * M_PI_2);
      } /*else {  // if ((ent2->get_pos().y - ent1->get_pos().y) == 0)
        // completely overlap, which is theoretically impossible...
        assert(false);
      }*/
    }

    event->angle_of_contact((M_PI - angle) / M_PI * 180);
  }
} /* entities_have_collided() */

void Arena::CheckForConeView(const class ArenaEntity * const ent,
                              const class Autobot * const aut,
                              EventSensor * event) {
  double range = ent->get_radius() + 7 * aut->get_radius();
  double y_dist = std::abs(aut->get_pos().y - ent->get_pos().y);
  double dist = std::sqrt(
      std::pow(aut->get_pos().x - ent->get_pos().x, 2) + 
      std::pow(aut->get_pos().y - ent->get_pos().y, 2));
  double angle_diff = (aut->get_heading_angle() / 180 * M_PI + 1)
    - std::asin(y_dist/dist);
  if (dist < range && angle_diff < 2) {
    event->collided(true);
    event->position(Position(aut->get_pos().x, aut->get_pos().y));
    event->heading_angle(aut->get_heading_angle());
  } else {
    event->collided(false);
  }

}


void Arena::Accept(__unused EventKeypress * e) {
  robot()->EventCmd(e->get_key_cmd());
}

NAMESPACE_END(csci3081);
