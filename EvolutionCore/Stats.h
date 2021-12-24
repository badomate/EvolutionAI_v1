#pragma once

#include "pch.h"

struct Stats {
	std::set<Position> botsPos;
	std::set<Position> foodPos;

	int botCount;
	int foodCount;

	int maxInnov;

	int stepNum;

	int maxGenCount;
};