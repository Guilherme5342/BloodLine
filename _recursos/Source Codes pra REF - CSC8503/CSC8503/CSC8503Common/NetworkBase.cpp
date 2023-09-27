#include "NetworkBase.h"

NetworkBase::NetworkBase()
{
	netHandle = nullptr;
}

NetworkBase::~NetworkBase()
{
	if (netHandle) {
		enet_host_destroy(netHandle);
	}
}

void NetworkBase::Initialise() {
	enet_initialize();
}

void NetworkBase::Destroy() {
	enet_deinitialize();
}