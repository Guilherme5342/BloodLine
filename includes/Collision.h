#include "Rect.h"
#include "Vector3.h"

#include <algorithm>
#include <cmath>

class Collision {

	public:
		// Observação: IsColliding espera ângulos em radianos!
		// Para usar graus, forneça a sua própria implementação de Rotate,
		// ou transforme os ângulos no corpo de IsColliding.
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
			Vector2 A[] = { Vector2( a.x, a.y + a.h ),
						  Vector2( a.x + a.w, a.y + a.h ),
						  Vector2( a.x + a.w, a.y ),
						  Vector2( a.x, a.y )
						};
			Vector2 B[] = { Vector2( b.x, b.y + b.h ),
						  Vector2( b.x + b.w, b.y + b.h ),
						  Vector2( b.x + b.w, b.y ),
						  Vector2( b.x, b.y )
						};

			for (auto& v : A) {
				v = Rotate(v - a.GetCenter(), angleOfA) + a.GetCenter();
			}

			for (auto& v : B) {
				v = Rotate(v - b.GetCenter(), angleOfB) + b.GetCenter();
			}

			Vector2 axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

			for (auto& axis : axes) {
				float P[4];

				for (int i = 0; i < 4; ++i)
					P[i] = Dot(A[i], axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i) 
					P[i] = Dot(B[i], axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB)
					return false;
			}

			return true;
		}

	private:

		static inline float Mag(const Vector2& p) {
			return std::sqrt(p.x * p.x + p.y * p.y);
		}

		static inline Vector2 Norm(const Vector2& p) {

			return Vector2(p.x,p.y) * (1.f - Mag(p));
		}

		static inline float Dot(const Vector2& a, const Vector2& b) {
			return a.x * b.x + a.y * b.y;
		}

		static inline Vector2 Rotate(const Vector2& p, float angle) {
			float cs = std::cos(angle), sn = std::sin(angle);
			return Vector2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
		}
};

// Aqui estão três operadores que sua classe Vector2 deve precisar, se já não tiver. 
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Vector2 operator+(const Vector2& rhs) const {
//    return Vector2(x + rhs.x, y + rhs.y);
// }

// Vector2 operator-(const Vector2& rhs) const {
//    return Vector2(x - rhs.x, y - rhs.y);
// }

// Vector2 operator*(const float rhs) const {
//    return Vector2(x * rhs, y * rhs);
// }