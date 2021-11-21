#pragma once

class NodeSHMInfo
{
public:
	NodeSHMInfo();
	~NodeSHMInfo();

	int status;
	int seckeyID;
	char clientID[12];
	char serverID[12];
	char seckey[128];
};

