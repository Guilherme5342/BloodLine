#pragma once
#include "Transform.h"
#include "BoundingVolume.h"
#include "PhysicsObject.h"
#include "RenderObject.h"
#include <vector>

using std::vector;

namespace NCL {
	namespace CSC8503 {
		class GameObject
		{
		public:
			GameObject(string name = "");

			~GameObject();

			void SetBoundingVolume(BoundingVolume* vol) {
				boundingVolume = vol;
			}

			const BoundingVolume* GetBoundingVolume() const {
				return boundingVolume;
			}

			bool IsActive() const {
				return isActive;
			}

			const Transform& GetConstTransform() const {
				return transform;
			}

			Transform& GetTransform() {
				return transform;
			}

			RenderObject* GetRenderObject() const {
				return renderObject;
			}

			void SetRenderObject(RenderObject* newObject) {
				renderObject = newObject;
			}

			void SetPhysicsObject(PhysicsObject* newObject) {
				physicsObject = newObject;
			}

			const string& GetName() const {
				return name;
			}

		protected:
			Transform			transform;

			BoundingVolume*		boundingVolume;
			PhysicsObject*		physicsObject;
			RenderObject*		renderObject;

			bool	isActive;
			string	name;
		};
	}
}

