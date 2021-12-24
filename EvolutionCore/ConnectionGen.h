#ifndef CONNECTION_H
#define CONNECTION_H
#include "pch.h"
#pragma once
class ConnectionGen
{
	float Weight;
	bool Enabled;
public:
	int Innov;
	int NodeIn;
	int NodeOut;
	ConnectionGen(int in, int out, float weight, int innov);
	void Disable();
	void Update(int in, int out, float weight);
	int ReadInnov() { return Innov; };
	float ReadWeight() { return Weight; };
	bool operator<(const ConnectionGen& rhs) const noexcept;
	bool operator==(const ConnectionGen& rhs) const noexcept;
};

#endif