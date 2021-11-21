#include "NodeSHMInfo.h"
#include <string.h>

NodeSHMInfo::NodeSHMInfo() : status(0), seckeyID(0)
{
	bzero(clientID, sizeof(clientID));
	bzero(serverID, sizeof(serverID));
	bzero(seckey, sizeof(seckey));
}


NodeSHMInfo::~NodeSHMInfo()
{
}
