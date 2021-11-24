#ifndef SIMULATION_H
#define SIMULATION_H

#include "Bot.h"
#include <iostream>

class Simulation {
	Bot makeBot(int lives, int inNodes, int outNodes, int width, int height, std::set<PositionNameSpace::Position>& foods, Mutation& mutations, int botNum);
public:
	void Start(int botCount, int foodCount, int steps, int inNode, int outNode, int lives, int width, int height);
};
#endif