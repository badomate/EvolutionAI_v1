#ifndef POS_H
#define POS_H

constexpr auto PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342;

#include <stdlib.h>
#include <time.h>
#include <math.h>

#pragma once
namespace PositionNameSpace {
	class Position {
	public:
		double X, Y;
		Position() {};
		Position(int, int);

		bool operator<(const Position& rhs) const noexcept {
			return this->X < rhs.X;
		}

		bool operator==(const Position& rhs) const noexcept {
			return this->X == rhs.X && this->Y == rhs.Y;
		};
		
	};

	Position GenerateRandomPos(int maxWidth, int maxHeight);
	double AngleCalc(Position point1, Position point2);
}

#endif