#ifndef	NODE_H
#define NODE_H

#pragma once
#include "Layers.h"
#include "pch.h"
class Node
{
	
public: 
	int NodeNum;
	mutable double fpValue = 0;

	Layers SensorType;
	Node(int num, Layers type);
	Node(int num) { NodeNum = num; };
	int readNum() {
		return NodeNum;
	};

	Layers readType();

	bool operator<(const Node& rhs) const noexcept {
		return this->NodeNum < rhs.NodeNum;
	};

	bool operator==(const Node& rhs) const noexcept {
		return this->NodeNum == rhs.NodeNum;
	}
};

#endif