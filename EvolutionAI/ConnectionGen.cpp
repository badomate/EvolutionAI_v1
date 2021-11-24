#include "ConnectionGen.h"

ConnectionGen::ConnectionGen(int in, int out, float weight, int innov)
{
	NodeIn = in;
	NodeOut = out;
	Weight = weight;
	Enabled = true;
	Innov = innov;
};

void ConnectionGen::Disable()
{
	Enabled = false;
};

void ConnectionGen::Update(int in, int out, float weight)
{
	NodeIn = in;
	NodeOut = out;
	Weight = weight;
};

bool ConnectionGen::operator<(const ConnectionGen& rhs) const noexcept
{
	return this->Innov < rhs.Innov;
};

bool ConnectionGen::operator==(const ConnectionGen& rhs) const noexcept
{
	return (this->NodeIn == rhs.NodeIn) && (this->NodeOut == rhs.NodeOut);
}

