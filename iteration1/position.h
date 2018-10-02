/**
 * @file common.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define NAMESPACE_BEGIN(csci3081) namespace csci3081 {
 
// This should be placed in front of any variable defined but not used to
// satisfy the compiler - otherwise a warning is given.
#define __unused __attribute__((unused))

struct Position {
Position(void) : x(0), y(0) { }
Position(int in_x, int in_y) : x(in_x), y(in_y) { }
  int x;
  int y;
};

#define NAMESPACE_END(csci3081) }

#endif  // SRC_COMMON_H_
