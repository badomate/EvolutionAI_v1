#ifndef CONNECTIONNODE_H
#define CONNECTIONNODE_H

#pragma once

class ConnectionNode
{
public:
	int InNodeNum;
	int OutNodeNum;
	int NextNodeNum;
	ConnectionNode(int in, int out)
	{
		InNodeNum = in;
		OutNodeNum = out;
	}
	ConnectionNode(int in, int out, int next)
	{
		InNodeNum = in;
		OutNodeNum = out;
		NextNodeNum = next;
	}
	bool operator<(const ConnectionNode& rhs) const noexcept {
		return this->NextNodeNum < rhs.NextNodeNum;
	}

	bool operator==(const ConnectionNode& rhs) const noexcept {
		return  (this->InNodeNum == rhs.InNodeNum) && (this->OutNodeNum == rhs.OutNodeNum);
	}
};

#endif