#pragma once
#include "../../Common/Vector2.h"
#include "Debug.h"
#include <list>
#include <functional>

namespace NCL {
	using namespace NCL::Maths;
	namespace CSC8503 {
		template<class T>
		class QuadTree;

		template<class T>
		class QuadTreeNode	{
		public:
			typedef std::function<void(std::list<T>&)> QuadTreeFunc;
		protected:
			friend class QuadTree<T>;

			QuadTreeNode() {
			}

			QuadTreeNode(QuadTree<T>&parent, Vector2 pos, Vector2 size) : parentTree(parent) {
				children		= nullptr;
				this->position	= pos;
				this->size		= size;
			}

			~QuadTreeNode() {
				delete[] children;
			}

			void Insert(T& object, int depthLeft, int maxSize) {
			}

			void Split() {
			}

			void DebugDraw() {
			}

			void OperateOnContents(QuadTreeFunc& func) {
			}

		protected:
			std::list<T>	contents;
			QuadTree<T>&	parentTree;

			Vector2 position;
			Vector2 size;

			QuadTreeNode<T>* children;
		};
	}
}


namespace NCL {
	using namespace NCL::Maths;
	namespace CSC8503 {
		template<class T>
		class QuadTree	{
		public:
			QuadTree(Vector2 size, int maxDepth = 6, int maxSize = 5) 
			: root(QuadTreeNode<T>(*this, Vector2(), size)){
				this->maxDepth	= maxDepth;
				this->maxSize	= maxSize;
			}
			~QuadTree() {
			}

			void Insert(T object) {
			}

			void DebugDraw() {
			}

			void OperateOnContents(typename QuadTreeNode<T>::QuadTreeFunc  func) {
			}

		protected:
			QuadTreeNode<T> root;
			int maxDepth;
			int maxSize;
		};
	}
}