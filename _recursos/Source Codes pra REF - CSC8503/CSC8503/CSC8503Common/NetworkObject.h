#pragma once
#include "GameObject.h"
#include "NetworkBase.h"
#include "NetworkState.h"
namespace NCL {
	namespace CSC8503 {
		struct FullPacket : public GamePacket {
			int		objectID;
			NetworkState fullState;

			FullPacket() {
				size = sizeof(FullPacket) + sizeof(int);
			}
		};

		struct DeltaPacket : public GamePacket {
			int		fullID;
			int		objectID;
			char	pos[3];
			char	orientation[4];

			DeltaPacket() {
				size = sizeof(DeltaPacket);
			}
		};

		struct ClientPacket : public GamePacket {
			int		lastID;
			char	buttonstates[8];

			ClientPacket() {
				size = sizeof(ClientPacket);
			}
		};

		class NetworkObject		{
		public:
			NetworkObject(GameObject& o, int id);
			virtual ~NetworkObject();

			//Called by clients
			virtual bool ReadPacket(GamePacket& p);
			//Called by servers
			virtual bool WritePacket(GamePacket** p, bool deltaFrame);

			void UpdateStateHistory(int minID);

		protected:

			NetworkState& GetLatestNetworkState();

			bool GetNetworkState(int frameID, NetworkState& state);


			virtual bool ReadDeltaPacket(DeltaPacket &p);
			virtual bool ReadFullPacket(FullPacket &p);

			virtual bool WriteDeltaPacket(GamePacket**p);
			virtual bool WriteFullPacket(GamePacket**p);

			GameObject& object;

			NetworkState lastFullState;

			std::vector<NetworkState> stateHistory;

			int latestState;

			int deltaErrors;
			int fullErrors;

			int networkID;
		};
	}
}

