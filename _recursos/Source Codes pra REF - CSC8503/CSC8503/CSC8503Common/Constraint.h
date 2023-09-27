#pragma once

namespace NCL {
	namespace CSC8503 {
		class Constraint	{
		public:
			Constraint() {}
			~Constraint() {}
			virtual void UpdateConstraint(float dt) = 0;
		};
	}
}

