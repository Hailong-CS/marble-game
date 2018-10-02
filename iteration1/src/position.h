/**
 * @file position.h
 *
 * @copyright 2017 3081 Hailong Zeng, All rights reserved.
 */

#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
#include "common.h"

NAMESPACE_BEGIN(csci3081);

struct Position {
 public:
  Position(void) : x(0), y(0) { }
  Position(double in_x, double in_y) : x(in_x), y(in_y) { }
   double x;
   double y;
};

NAMESPACE_END(csci3081);

#endif  // SRC_POSITION_H_
