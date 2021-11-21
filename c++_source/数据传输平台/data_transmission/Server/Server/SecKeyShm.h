#pragma once
#include "BaseShm.h"
#include <string.h>
#include "NodeSHMInfo.h"

class SecKeyShm : public BaseShm
{
public:
	SecKeyShm(int key, int maxNode);
	SecKeyShm(string pathName, int maxNode);
	~SecKeyShm();

	void shmInit();
	int shmWrite(NodeSHMInfo* pNodeInfo);
	NodeSHMInfo shmRead(string clientID, string serverID);

private:
	int m_maxNode;
};

