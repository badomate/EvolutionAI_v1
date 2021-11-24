#ifndef GENOME_H
#define GENOME_H

#pragma once
#include <set>
#include "Node.h"
#include "Mutation.h"

class Genome
{
	std::set<Node> InputNodes;
	std::set<Node> OutputNodes;
	std::set<Node> HiddenNodes;

	std::set<ConnectionGen> ConnectionGenes;

	void AddHiddenNode(Node node);
	void AddInputNode(Node node);
	void AddOutputNode(Node node);
	float RemoveConnection(int in, int out, Mutation& mutations);
public:
	void AddConnection(int input, int output, Mutation& mutations);
	void AddConnection(int input, int otput, float weight, Mutation& mutations);
	void AddNonHiddenLayers(int inputNodes, int outputNodes);
	void AddNode(int in, int out, Mutation& mutations);
	void AddRandomMutation(Mutation& mutations, int chanceMax);
	std::set<Node> readInputNodes() { return InputNodes; };
	std::set<Node> readOutputNodes() { return OutputNodes; };
	std::set<Node> readHiddenNodes() { return HiddenNodes; };
};

#endif