#include "pch.h"

Bot::Bot(int lives)
{
	Lives = lives;

}

Position Bot::findClosestFood(std::set<Position> foods)
{
	Position closest;
	int dist = -1;
	for (auto food : foods)
	{
		int dist2 = abs(food.X - Pos.X) + abs(food.Y - Pos.Y);

		if (dist2 < dist || dist < 0)
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

	outNodes: Up
			  Down
			  Right
			  Left

	*/

	std::set<Node>::iterator it = Gen.InputNodes.begin();

	/*(*it).fpValue = Lives;

	it++;*/
	(*it).fpValue = ClosestFood.X - Pos.X;

	it++;
	(*it).fpValue = ClosestFood.Y - Pos.Y;

	/*it++;
	(*it).fpValue = ClosestFood.X;

	it++;
	(*it).fpValue = ClosestFood.Y;

	it++;*/
	/*(*it).fpValue = ClosestFoodAngle;*/


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

		itOut->fpValue += sigmoid(itIn->fpValue) * con.ReadWeight();
	}

	double output[4] = { 0 };
	int c = 0;
	for (auto it = Gen.OutputNodes.begin(); it != Gen.OutputNodes.end(); it++)
	{
		output[c] = (*it).fpValue;
		c++;
	}

	Dir[0] = (output[0]  >= output[1]) ? 0 : 1;
	Dir[0] = (output[2] >= output[3]) ? 0 : 1;

	
	

}


void Bot::Update(int maxX, int maxY, int c)
{
	//std::cout << Pos.X << "  ";
	/*if ((((Pos.X + cos(BotAngle)) > 0) && ((Pos.X += cos(BotAngle)) <= maxX)))
		if (Pos.X > maxX)
			int x = 0;
		else
			Pos.X += cos(BotAngle);

	if ((((Pos.Y + sin(BotAngle)) > 0) && ((Pos.Y += sin(BotAngle)) <= maxY)))
		if (Pos.Y > maxY)
			int y = 0;
		else
			Pos.Y += sin(BotAngle);*/
	int leendoX = this->Pos.X;
	int leendoY = this->Pos.Y;
	leendoX += (Dir[1] == 0) ? 1 : -1;
	leendoY += (Dir[0] == 0) ? 1 : -1;

	if (0. < leendoX && leendoX < (double)maxX)
		Pos.X = leendoX;

	if (0. < leendoY && leendoY < (double)maxY)
		Pos.Y = leendoY;


	//std::cout << Pos.X << std::endl;
}

bool Bot::DidEat()
{
	double dist = sqrt(pow((Pos.X - ClosestFood.X), 2) + pow((Pos.Y - ClosestFood.Y), 2));

	return (dist <= 1) ? true : false;
}