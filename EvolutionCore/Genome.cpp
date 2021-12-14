#include "pch.h"



void Genome::AddHiddenNode(Node node)
{
	HiddenNodes.insert(node);
}

void Genome::AddInputNode(Node node)
{
	InputNodes.insert(node);
}

void Genome::AddOutputNode(Node node)
{
	OutputNodes.insert(node);
}

void Genome::AddConnection(int input, int output, Mutation& mutations)
{
	int innov = mutations.FindInnov(input, output);
	float weight = (rand() % 10000) / static_cast<float>(10000);
	ConnectionGenes.insert(ConnectionGen(input, output, weight, innov));

}

void Genome::AddConnection(int input, int output, float weight, Mutation& mutations)
{
	int innov = mutations.FindInnov(input, output);
	ConnectionGenes.insert(ConnectionGen(input, output, weight, innov));

}

float Genome::RemoveConnection(int in, int out, Mutation& mutations)
{
	int innov = mutations.FindInnov(in, out);
	
	std::set<ConnectionGen>::iterator it;
	

	for (it = ConnectionGenes.begin(); it != ConnectionGenes.end(); it++)
	{
		if (ConnectionGenes.find(*it) != ConnectionGenes.end())
		{
			auto helper = *it;

			helper.Disable();
			ConnectionGenes.erase(*it);
			ConnectionGenes.insert(helper);
			return helper.ReadWeight();
		}
	}

	return 0.f;
}

void Genome::AddNode(int in, int out, Mutation& mutations)
{
	float weight = RemoveConnection(in, out, mutations);
	int nodeNum = mutations.FindNodeNum(in, out);

	AddHiddenNode(Node(nodeNum, Layers::HIDDEN));

	AddConnection(in, nodeNum, 1.f, mutations);
	AddConnection(nodeNum, out, weight, mutations);
}

void Genome::AddNonHiddenLayers(int inputNodes, int outputNodes)
{
	for (int i = 1; i <= inputNodes; i++)
	{
		AddInputNode(Node(i, Layers::INPUT));
	}
	for (int i = inputNodes + 1; i <= inputNodes + outputNodes; i++)
	{
		AddOutputNode(Node(i, Layers::OUTPUT));
	}
}

void Genome::AddRandomMutation(Mutation& mutations, int chanceMax)
{
		while (true)
		{
			int chance = rand() % chanceMax;
			if (chance != 1)
			{
				return;
			}

			chance = rand() % 2 + 1;

			if (chance <= 2)
			{
				//add random connection
				int input = InputNodes.size();
				int output = OutputNodes.size();
				int hidden = HiddenNodes.size();

				int first = rand() % (input + hidden) + 1;
				int second = rand() % (output + hidden) + input + 1;
				int firstNodeNum;
				if (input >= first)
				{
					auto it = InputNodes.begin();
					auto node = *it;

					while (node.NodeNum != first && it != InputNodes.end())
					{
						it++;
						node = *it;
					}

					firstNodeNum = node.readNum();
				}
				else
				{
					auto it = HiddenNodes.begin();
					auto node = *it;
					for (int i = 1; i < first - (output + input); i++) { it++; }
					node = *it;
					firstNodeNum = node.readNum();
				}

				int secondNodeNum;
				if (output + input >= second)
				{
					

					auto it = OutputNodes.begin();
					auto node = *it;
					while (node.NodeNum != second && it != OutputNodes.end())
					{
						it++;
						node = *it;
					}
					secondNodeNum = node.readNum();
				}
				else
				{
					auto it = HiddenNodes.begin();
					auto node = *it;
					for (int i = 1; i < second - (output + input); i++) { it++; }
					node = *it;
					secondNodeNum = node.readNum();
				}

				AddConnection(firstNodeNum, secondNodeNum, mutations);
			}
			if (chance == 1)
			{
				int max = ConnectionGenes.size();
				int randomConnection = rand() % max + 1;

				auto it = ConnectionGenes.begin();
				for (int i = 1; i < randomConnection; i++) { it++; }
				auto connection = *it;

				AddNode(connection.NodeIn, connection.NodeOut, mutations);
			}
		}

}