#ifndef SIMULATION_H
#define SIMULATION_H

#include "Bot.h"
#include <iostream>
#include <thread>
#include <vector>

class Simulation {

	int steps;

	int inNodesCount, outNodesCount;

	int starterLives;

	int width, height;

	std::vector<Bot> bots;
	Mutation mutations;
	std::set<Position> foods;

	bool isRunning;

	Bot makeBot(int lives, int inNodes, int outNodes, int width, int height, std::set<PositionNameSpace::Position>& foods, Mutation& mutations);
	void doGeneration();
public:
	Simulation() {};
	void Innit(int botCount, int foodCount, int steps, int inNode, int outNode, int lives, int width, int height);

	void Start();
	void End();
	void Reset();

	std::set<Position> ReadState();
	std::set<Position> ReadFood() { return foods; };
		
};
#endif