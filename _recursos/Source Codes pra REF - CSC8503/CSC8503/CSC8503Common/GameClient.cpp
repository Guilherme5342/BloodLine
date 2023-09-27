#include "GameClient.h"
#include <iostream>
#include <string>

using namespace NCL;
using namespace CSC8503;

GameClient::GameClient()	{
	netHandle = enet_host_create(nullptr, 1, 1, 0, 0);
}

GameClient::~GameClient()	{
	threadAlive = false;
	updateThread.join();
	enet_host_destroy(netHandle);
}

bool GameClient::Connect(uint8_t a, uint8_t b, uint8_t c, uint8_t d, int portNum) {
	return false;
}

void GameClient::UpdateClient() {

}

void GameClient::SendPacket(GamePacket&  payload) {

}

void GameClient::ThreadedUpdate() {
	while (threadAlive) {
		UpdateClient();
		std::this_thread::yield();
	}
}
