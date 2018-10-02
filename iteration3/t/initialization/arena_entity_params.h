/**
 * @file arena_entity_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef ARENA_ENTITY_PARAMS_H_
#define ARENA_ENTITY_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "position.h"
#include "color.h"



/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct arena_entity_params {
	arena_entity_params(void) : radius(), pos(), color() {}
	double radius;
	Position pos;
	Color color;
};


#endif /* ARENA_ENTITY_PARAMS_H_ */
