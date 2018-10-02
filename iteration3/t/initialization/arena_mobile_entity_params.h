/**
 * @file arena_mobile_entity_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef ARENA_MOBILE_ENTITY_PARAMS_H_
#define ARENA_MOBILE_ENTITY_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "arena_entity_params.h"


/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct arena_mobile_entity_params : public arena_entity_params {
  arena_mobile_entity_params(void) : arena_entity_params(),
                               collision_delta() {}

  double collision_delta;
};


#endif /* ARENA_MOBILE_ENTITY_PARAMS_H_ */
