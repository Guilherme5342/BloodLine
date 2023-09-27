#pragma once
#include "../../Common/Vector3.h"

namespace NCL {
	namespace Maths {
		class Simplex	{
		public:
			struct SupportPoint {
				Vector3 pos;
				Vector3 onA;
				Vector3 onB;
			};

			Simplex();
			~Simplex();

			void SetToTri(SupportPoint a, SupportPoint b, SupportPoint c);

			void SetToLine(SupportPoint a, SupportPoint b);

			void Add(SupportPoint a);

			int GetSize() const {
				return size;
			}

			Vector3 GetVertex(int i) const {
				return verts[IndexToSlot(i)].pos;
			}

			SupportPoint GetSupportPoint(int i) const {
				return verts[IndexToSlot(i)];
			}

			void RemoveOldestSupportPoint();

			float GetClosestDistance();

			Vector3 ReduceToClosestSimplex();

		protected:
			int IndexToSlot(int i) const {
				int slot = (index - 1) - i;
				if (slot < 0) {
					slot += size;
				}
				return slot;
			}

			SupportPoint verts[4];
			int index;
			int size;
		};
	}
}

