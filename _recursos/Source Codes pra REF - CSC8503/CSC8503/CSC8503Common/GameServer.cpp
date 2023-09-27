#include "GameServer.h"
#include "GameWorld.h"
#include <iostream>

using namespace NCL;
using namespace CSC8503;

GameServer::GameServer(int onPort, int maxClients)	{
	port		= onPort;
	clientMax	= maxClients;
	clientCount = 0;
	netHandle	= nullptr;
	threadAlive = false;

	Initialise();
}

GameServer::~GameServer()	{
	Shutdown();
}

void GameServer::Shutdown() {
	SendGlobalMessage(BasicNetworkMessages::Shutdown);

	threadAlive = false;
	updateThread.join();

	enet_host_destroy(netHandle);
	netHandle = nullptr;
}

bool GameServer::Initialise() {
	return true;
}

bool GameServer::SendGlobalMessage(int msgID) {
	return true;
}

bool GameServer::SendGlobalMessage(GamePacket& packet) {
	return true;
}

void GameServer::UpdateServer() {

}

void GameServer::ThreadedUpdate() {
	while (threadAlive) {
		UpdateServer();
		std::this_thread::yield();
	}
}

//Second networking tutorial stuff

void GameServer::SetGameWorld(GameWorld &g) {
	gameWorld = &g;
}

void GameServer::BroadcastSnapshot(bool deltaFrame) {

}

void GameServer::UpdateMinimumState() {

}