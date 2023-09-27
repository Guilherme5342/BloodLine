#pragma once
#include "../../Common/Vector3.h"
#include "../../Common/Quaternion.h"

namespace NCL {
	using namespace Maths;
	namespace CSC8503 {
		class GameObject;
		class NetworkState	{
		public:
			NetworkState() {
				stateID = 0;
			}
			virtual ~NetworkState();

			Vector3		position;
			Quaternion	orientation;
			int			stateID;
		};
	}
}

