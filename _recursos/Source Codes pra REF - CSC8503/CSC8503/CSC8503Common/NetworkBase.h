#pragma once
#include <enet/enet.h>
#include <map>
#include <string>

enum BasicNetworkMessages {
	None,
	Hello,
	Message,
	String,
	Delta_State,	//1 byte per channel since the last state
	Full_State,		//Full transform etc
	Received_State, //received from a client, informs that its received packet n
	Player_Connected,
	Player_Disconnected,
	Shutdown
};

struct GamePacket {
	short size;
	short type;

	GamePacket() {
		type		= BasicNetworkMessages::None;
		size		= 0;
	}

	GamePacket(short type) {
		this->type	= type;
	}

	int GetTotalSize() {
		return sizeof(GamePacket) + size;
	}
};

struct StringPacket : public GamePacket {
	char	stringData[256];

	StringPacket(const std::string& message) {
		type		= BasicNetworkMessages::String;
		size		= (short)message.length();

		memcpy(stringData, message.data(), size);
	};

	std::string GetStringFromData() {
		std::string realString(stringData);
		realString.resize(size);
		return realString;
	}
};

struct NewPlayerPacket : public GamePacket {
	int playerID;
	NewPlayerPacket(int p ) {
		type		= BasicNetworkMessages::Player_Connected;
		playerID	= p;
		size		= sizeof(int);
	}
};

struct PlayerDisconnectPacket : public GamePacket {
	int playerID;
	PlayerDisconnectPacket(int p) {
		type		= BasicNetworkMessages::Player_Disconnected;
		playerID	= p;
		size		= sizeof(int);
	}
};

class PacketReceiver {
public:
	virtual void ReceivePacket(int type, GamePacket* payload) = 0;
};

class NetworkBase	{
public:
	static void Initialise();
	static void Destroy();

	static int GetDefaultPort() {
		return 1234;
	}

	void RegisterPacketHandler(int msgID, PacketReceiver* receiver) {
		packetHandlers.insert(std::make_pair(msgID, receiver));
	}

protected:
	NetworkBase();
	~NetworkBase();

	typedef std::multimap<int, PacketReceiver*>::const_iterator PacketHandlerIterator;

	bool GetPackethandlers(int msgID, PacketHandlerIterator& first, PacketHandlerIterator& last) const {
		auto range = packetHandlers.equal_range(msgID);

		if (range.first == packetHandlers.end()) {
			return false; //no handlers for this message type!
		}
		first	= range.first;
		last	= range.second;
		return true;
	}

	ENetHost* netHandle;

	std::multimap<int, PacketReceiver*> packetHandlers;
};