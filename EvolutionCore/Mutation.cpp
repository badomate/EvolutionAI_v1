#include "pch.h"


auto Mutation::SearchConnection(int in, int out)
{
	std::set<ConnectionGen>::iterator it;
	it = PreviousConnections.begin();
	while (it != PreviousConnections.end())
	{
		if (*it == ConnectionGen(in, out, 1.f, 1))
		{
			return it;
		}
		it++;
	}
	return PreviousConnections.end();
}

void Mutation::addConnection(int in, int out, int innov)
{
	PreviousConnections.insert(ConnectionGen(in, out, 0.f, innov));
}

void Mutation::addNode(int in, int out, int innov)
{
	PreviousNodeMutations.insert(ConnectionNode(in, out, innov));
}

int Mutation::FindInnov(int in, int out)
{
	auto it = SearchConnection(in, out);
	if (it != PreviousConnections.end())
	{
		ConnectionGen helper =  *it;
		return helper.ReadInnov();
	}
	else
	{
		InnovCount++;
		addConnection(in, out, InnovCount);
		return InnovCount;
	}

}

int Mutation::FindNodeNum(int in, int out)
{
	auto it = PreviousNodeMutations.find(ConnectionNode(in, out));
	if (it != PreviousNodeMutations.end())
	{
		ConnectionNode helper = *it;
		return helper.NextNodeNum;
	}
	else
	{
		NodeCount++;
		addNode(in, out, NodeCount);
		return NodeCount;
	}


}

