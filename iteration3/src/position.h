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
#include <algorithm>
#include "src/common.h"

NAMESPACE_BEGIN(csci3081);

struct Position {
	public:
		Position(void) : x(0), y(0) { }
		Position(double in_x, double in_y) : x(in_x), y(in_y) { }
		double x;
		double y;
 		// operator - will get the distance between two position
		friend double operator- (const Position& p1, const Position& p2) {
			double dist;
			dist = std::sqrt(
				std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y),2));

			return dist;
		}
};

NAMESPACE_END(csci3081);

#endif  // SRC_POSITION_H_
