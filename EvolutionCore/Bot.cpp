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