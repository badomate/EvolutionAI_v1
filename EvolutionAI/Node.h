#ifndef	NODE_H
#define NODE_H

#pragma once
#include "Layers.h"
class Node
{
	
public: 
	int NodeNum;
	Layers SensorType;
	Node(int num, Layers type);

	int readNum() {
		return NodeNum;
	};

	Layers readType();

	bool operator<(const Node& rhs) const noexcept {
		return this->NodeNum < rhs.NodeNum;
	};
};

#endif