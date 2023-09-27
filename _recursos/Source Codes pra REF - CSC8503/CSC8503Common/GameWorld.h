#pragma once
#include <vector>
#include "../Common/Ray.h"
namespace NCL {
		class Camera;
		using Maths::Ray;
	namespace CSC8503 {
		class GameObject;


		class GameWorld
		{
		public:
			GameWorld();
			~GameWorld();

			void Clear();
			void ClearAndErase();

			void AddGameObject(GameObject* o);
			void RemoveGameObject(GameObject* o);

			Camera* GetMainCamera() const {
				return mainCamera;
			}

			bool Raycast(Ray& r, GameObject** o) const;

			void UpdateWorld(float dt, bool updateCamera);

			void UpdateTransforms();

			void GetObjectIterators(
				std::vector<GameObject*>::const_iterator& first,
				std::vector<GameObject*>::const_iterator& last) const;

		protected:
			std::vector<GameObject*> gameObjects;

			Camera* mainCamera;
		};
	}
}

