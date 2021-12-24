#ifndef MUTATION_H
#define MUTATION_H
#include "ConnectionGen.h"
#include <set>
#include "ConnectionNode.h"
#pragma once


class Mutation
{
	std::set<ConnectionGen> PreviousConnections;
	std::set<ConnectionNode> PreviousNodeMutations;
	int InnovCount;
	int NodeCount;
	auto SearchConnection(int in, int out);
	void addConnection(int in, int out, int innov);
	void addNode(int in, int out, int innov);
public:
	Mutation() {};
	Mutation(int startetNodes) { NodeCount = startetNodes; InnovCount = 0; };
	int ReadInnov() { return InnovCount; };
	int FindInnov(int in, int out);
	int FindNodeNum(int in,int out);
};

#endif