#ifndef SIMULATION_H
#define SIMULATION_H

#include "Bot.h"
#include <iostream>
#include <thread>


class Simulation {

	std::set<Bot> bots;
	Mutation mutations;
	std::set<Position> foods;
	bool isRunning;
	int x = 0;
	Bot makeBot(int lives, int inNodes, int outNodes, int width, int height, std::set<PositionNameSpace::Position>& foods, Mutation& mutations, int botNum);
	void doGeneration();
public:
	Simulation() {};
	void Innit(int botCount, int foodCount, int steps, int inNode, int outNode, int lives, int width, int height);

	void Start();
	void End();
	void Reset();

	int read() { return x; };

	std::set<Bot> ReadState() { return bots; };
	Mutation ReadMutations() { return mutations; };
	std::set<Position> ReadFood() { return foods; };
		
};
#endif