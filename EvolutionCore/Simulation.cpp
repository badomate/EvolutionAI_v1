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

	this->steps = steps;
	this->inNodesCount = inNodes;
	this->outNodesCount = outNodes;
	this->starterLives = lives;
	this->width = width;
	this->height = height;

	mutations = Mutation(inNodes + outNodes);

	for (int i = 0; i < foodCount; i++)
		foods.insert(PositionNameSpace::GenerateRandomPos(width, height));

	for (int i = 0; i < botCount; i++)
	{

		Bot botBeggin = makeBot(lives, inNodes, outNodes, width, height, foods, mutations);

		bots.push_back(botBeggin);
	}
}

Bot Simulation::makeBot(int lives, int inNodes, int outNodes, int width, int height, std::set<PositionNameSpace::Position>& foods, Mutation& mutations)
{
	Bot botBeggin = Bot(lives);
	Genome gen;

	gen.AddNonHiddenLayers(inNodes, outNodes);

	gen.AddRandomMutation(mutations, 5);
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

	using namespace std::literals::chrono_literals;

	while (isRunning)
	{

		std::vector<Bot>::iterator botIt;
		std::vector<Bot> newBots;
		std::vector<Position> eatenFoods;

		for (botIt = bots.begin(); botIt != bots.end(); botIt++)
		{
			(*botIt).Lives -= 1;
			if (!(*botIt).Alive)
				continue;
			if ((*botIt).Lives == 0)
				(*botIt).Alive = false;

			(*botIt).ForwardPass();
			(*botIt).Update(width, height, 0);
			Position closestFood = (*botIt).findClosestFood(foods);
			(*botIt).addClosestFood(closestFood);


			if (!(*botIt).DidEat())
			{
				double angle = PositionNameSpace::AngleCalc((*botIt).readPos(), closestFood);
				(*botIt).addClosestFoodAngle(angle);
				continue;
			}

			Position newFood = PositionNameSpace::GenerateRandomPos(width, height);
			foods.insert(newFood);

			eatenFoods.push_back(closestFood);

			Bot newBot = Bot(this->starterLives);
			newBot.addGen((*botIt).Gen);
			newBot.addPos((*botIt).readPos());
			newBot.addSpeed((*botIt).readSpeed());

			double botAngle = (rand() % 180);
			newBot.addBotAngle(botAngle);

			closestFood = newBot.findClosestFood(foods);
			newBot.addClosestFood(closestFood);

			double angle = PositionNameSpace::AngleCalc(closestFood, newBot.readPos());
			newBot.addClosestFoodAngle(angle);

			newBot.Gen.AddRandomMutation(mutations, 5);

			newBots.push_back(newBot);

		}

		for (int i = 0; i < newBots.size(); i++)
			bots.push_back(newBots[i]);

		for (int i = 0; i < eatenFoods.size(); i++)
			if (foods.find(eatenFoods[i]) != foods.end())
				foods.erase(eatenFoods[i]);

		//std::this_thread::sleep_for(0.01s);
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

std::set<Position> Simulation::ReadState()
{
	std::set<Position> pos;
	for (int i = 0; i < bots.size(); i++)
		if (bots[i].Alive)
			pos.insert(Position(round(bots[i].readPos().X), round(bots[i].readPos().Y)));

	return pos;
}