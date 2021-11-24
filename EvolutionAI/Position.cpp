#include "Position.h"


using PositionNameSpace::Position;

Position::Position(int x, int y)
{
	X = x;
	Y = y;
}
Position PositionNameSpace::GenerateRandomPos(int maxWidth, int maxHeight)
{
	int width = rand() % maxWidth;
	int height = rand() % maxHeight;

	return Position::Position(width, height);
}

double PositionNameSpace::AngleCalc(Position point1, Position point2)
{
	return atan2(point1.Y-point2.Y, point1.X-point2.X)*180/PI;
}