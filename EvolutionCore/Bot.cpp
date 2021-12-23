#include "pch.h"

Bot::Bot(int lives, int botNum)
{
	Lives = lives;
	BotNum = botNum;

}

Position Bot::findClosestFood(std::set<Position> foods)
{
	Position closest;
	int dist = -1;
	for (auto food : foods)
	{
		int dist2 = abs(food.X - Pos.X) + abs(food.Y - Pos.Y);

		if ( dist2 < dist || dist < 0)
		{
			closest = food;
			dist = dist2;
		}
	}

	return closest;
}

double sigmoid(double z)
{
	z = max(-60.0, min(60.0, 5.0 * z));
	return 1.0 / (1.0 + exp(z));
}

void Bot::ForwardPass()
{
	/*

	inNodes: Lives
			 Pos_X
			 Pos_y
			 ClosestFood_x
			 ClosestFood_y
			 ClosestFood_Angle

	outNodes: BotAngle

	*/

	std::set<Node>::iterator it = Gen.InputNodes.begin();
	
	(*it).fpValue = Lives;

	it++;
	(*it).fpValue = Pos.X;
	
	it++;
	(*it).fpValue = Pos.Y;
	
	it++;
	(*it).fpValue = ClosestFood.X;
	
	it++;
	(*it).fpValue = ClosestFood.Y;

	it++;
	(*it).fpValue = ClosestFoodAngle;
	double last = BotAngle;
	for (ConnectionGen con : Gen.ConnectionGenes)
	{
		std::set<Node>::iterator itOut;
		itOut = Gen.HiddenNodes.find(Node(con.NodeOut));

		if (itOut == Gen.HiddenNodes.end())
			itOut = Gen.OutputNodes.find(Node(con.NodeOut));

		std::set<Node>::iterator itIn;
		itIn = Gen.HiddenNodes.find(Node(con.NodeIn));

		if (itIn == Gen.HiddenNodes.end())
			itIn = Gen.InputNodes.find(Node(con.NodeIn));

		itOut->fpValue += sigmoid(itIn->fpValue)*con.ReadWeight();
		last = itOut->fpValue;
	}
	
	BotAngle = last;

	std::cout << last << std::endl;
}
