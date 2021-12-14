#ifndef BOT_H
#define BOT_H


#include "Position.h"
#include "Genome.h"
#include "pch.h"
using PositionNameSpace::Position;

class Bot {
	int Lives;
	Position Pos;
	Position ClosestBot;
	double ClosestBotAngle;
	Position ClosestFood;
	double ClosestFoodAngle;
	double Speed;
	double BotAngle;
	int BotNum;

public:
	Genome Gen;
	Bot(int lives, int botnum);
	void addGen(Genome gen) { this->Gen = gen; };
	void addPos(Position pos) { Pos = pos; };
	void addClosestFood(Position food) { ClosestFood = food; };
	void addClosestFoodAngle(double angle) { ClosestFoodAngle = angle; };
	void addClosestBot(Position bot) { ClosestBot = bot; };
	void addClosestBotAngle(double angle) { ClosestBotAngle = angle; };
	void addSpeed(double speed) { Speed = speed; };
	void addBotAngle(double angle) { BotAngle = angle; };

	Position findClosestFood(std::set<Position> foods);
	Position findClosestBot(std::set<Bot> bots, Bot bot) { return bot.readPos(); };

	Genome readGen() { return Gen; };
	int readLives() { return Lives; };
	Position readPos() { return Pos; };
	Position readClosestBot() { return ClosestBot; };
	float readClosestBotAngle() { return ClosestBotAngle; };
	float readClosestFoodAngle() { return ClosestFoodAngle; };
	Position readClosestFood() { return ClosestFood; };
	float readSpeed() { return Speed; };
	float readBotAngle() { return BotAngle; };


	bool operator<(const Bot& rhs) const noexcept {
		return this->BotNum < rhs.BotNum;
	};
};

#endif