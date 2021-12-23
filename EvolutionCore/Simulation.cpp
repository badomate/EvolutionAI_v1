#include "pch.h"

void Simulation::Innit(int botCount, int foodCount, int steps, int inNodes, int outNodes, int lives, int width, int height)
{
	/*
	
	inNodes: Lives
			 Pos_X
			 Pos_y
			 ClosestFood_x
			 ClosestFood_y
			 ClosestFood_Angle
			 
	outNodes: Speed
			  BotAngle
			 
	*/
	mutations = Mutation(inNodes + outNodes);

	for (int i = 0; i < foodCount; i++)
		foods.insert(PositionNameSpace::GenerateRandomPos(width, height));

	for (int i = 0; i < botCount; i++)
	{

		Bot botBeggin = makeBot(lives, inNodes, outNodes, width, height, foods, mutations, i);

		bots.insert(botBeggin);
	}
}

Bot Simulation::makeBot(int lives, int inNodes, int outNodes, int width, int height, std::set<PositionNameSpace::Position>& foods, Mutation& mutations, int botNum)
{
	Bot botBeggin = Bot(lives, botNum);
	Genome gen;

	gen.AddNonHiddenLayers(inNodes, outNodes);
	for (int j = 0; j < 10; j++)
		gen.AddRandomMutation(mutations, 10);
	botBeggin.addGen(gen);


	float speed = (rand() % 200) / 100 + 0.6;
	botBeggin.addSpeed(speed);

	Position closestFood = botBeggin.findClosestFood(foods);
	botBeggin.addClosestFood(closestFood);

	double botAngle = (rand() % 180);
	botBeggin.addBotAngle(botAngle);
	botBeggin.addPos(PositionNameSpace::GenerateRandomPos(width, height));

	double angle = PositionNameSpace::AngleCalc(closestFood, botBeggin.readPos());
	botBeggin.addClosestFoodAngle(angle);

	return botBeggin;
}

void Simulation::doGeneration() {
	x = 0;

	using namespace std::literals::chrono_literals;

	while (isRunning)
	{
		x += 1;
		for (Bot currentBot: bots)
		{
			currentBot.ForwardPass();
		}
		std::this_thread::sleep_for(0.2s);
	}
}

void Simulation::Start() {

	isRunning = true;
	std::thread evolve(&Simulation::doGeneration, this);

	evolve.detach();

}

void Simulation::End() {
	isRunning = false;
}

void Simulation::Reset() {

}

