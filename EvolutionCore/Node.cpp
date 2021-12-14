#include "pch.h"


Node::Node(int num, Layers type)
{
	NodeNum = num;
	SensorType = type;
}

Layers Node::readType()
{
	return SensorType;
}