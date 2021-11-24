#include "Simulation.h"

void Simulation::Start(int botCount, int foodCount, int steps, int inNodes, int outNodes, int lives, int width, int height)
{
	std::set<Bot> bots;
	Mutation mutations = Mutation(inNodes + outNodes);

	std::set<PositionNameSpace::Position> foods;
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