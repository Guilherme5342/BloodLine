#pragma once
#include "../Common/Vector3.h"

using namespace NCL::Maths;

namespace NCL {
	class BoundingVolume;
	

	namespace CSC8503 {
		class Transform;

		class PhysicsObject
		{
		public:
			PhysicsObject(Transform* parentTransform, const BoundingVolume* parentVolume);
			~PhysicsObject();

			Vector3 GetLinearVelocity() const {
				return linearVelocity;
			}

			Vector3 GetAcceleration() const {
				return acceleration;
			}

			Vector3 GetAngularVelocity() const {
				return angularVelocity;
			}

			Vector3 GetTorque() const {
				return torque;
			}

			
			void AddForce(const Vector3& force);

			void AddForceAtPosition(const Vector3& force, const Vector3& position);

			void AddTorque(const Vector3& torque);


			void ClearForces();


		protected:
			const BoundingVolume* volume;
			Transform*		transform;

			float inverseMass;
			float elasticity;
			float friction;

			//linear stuff
			Vector3 linearVelocity;
			Vector3 acceleration;

			//angular stuff
			Vector3 angularVelocity;
			Vector3 torque;
		};
	}
}

