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

		itOut->fpValue += sigmoid(itIn->fpValue) * con.ReadWeight();
		last = itOut->fpValue;
	}

	BotAngle = last;

	//std::cout << last << std::endl;
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

	double leendoX = Pos.X + cos(BotAngle);
	double leendoY = Pos.Y + sin(BotAngle);

	if (0. < leendoX && leendoX < (double)maxX)
		Pos.X = leendoX;
	else if(c == 0)
	{
		BotAngle *= -1; 
		Update(maxX, maxY, 1);
	}

	if (0. < leendoY && leendoY < (double)maxY)
		Pos.Y = leendoY;
	else if(c == 0)
	{
		BotAngle *= -1;
		Update(maxX, maxY, 1);
	}
		

	//std::cout << Pos.X << std::endl;
}

bool Bot::DidEat()
{
	double dist = sqrt(pow((Pos.X - ClosestFood.X), 2) + pow((Pos.Y - ClosestFood.Y), 2));

	return (dist <= 1) ? true : false;
}