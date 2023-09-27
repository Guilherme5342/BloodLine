#pragma once
#include <thread>
#include <atomic>

#include "NetworkBase.h"

namespace NCL {
	namespace CSC8503 {
		class GameWorld;
		class GameServer : public NetworkBase {
		public:
			GameServer(int onPort, int maxClients);
			~GameServer();

			bool Initialise();
			void Shutdown();

			void SetGameWorld(GameWorld &g);

			void ThreadedUpdate();

			bool SendGlobalMessage(int msgID);
			bool SendGlobalMessage(GamePacket& packet);

			void BroadcastSnapshot(bool deltaFrame);
			void UpdateMinimumState();

		protected:
			int			port;
			int			clientMax;
			int			clientCount;
			GameWorld*	gameWorld;

			std::atomic<bool> threadAlive;

			virtual void UpdateServer();

			std::thread updateThread;

			int incomingDataRate;
			int outgoingDataRate;

			std::map<int, int> stateIDs;
		};
	}
}
