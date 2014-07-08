#include <cmath>
#include <algorithm>
#include "Point.h"
#include "Rect.h"


class Collision {

public:
	static inline bool IsColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB) {
		Point A[] = { Point(a.GetXrect(), a.GetYrect() + a.GetHrect()),
			Point(a.GetXrect() + a.GetWrect(), a.GetYrect() + a.GetHrect()),
			Point(a.GetXrect() + a.GetWrect(), a.GetYrect()),
			Point(a.GetXrect(), a.GetYrect())
		};
		Point B[] = { Point(b.GetXrect(), b.GetYrect() + b.GetHrect()),
			Point(b.GetXrect() + b.GetWrect(), b.GetYrect() + b.GetHrect()),
			Point(b.GetXrect() + b.GetWrect(), b.GetYrect()),
			Point(b.GetXrect(), b.GetYrect())
		};

		for (auto& v : A) {
			v = Rotate(v - a.CenterRect(a), angleOfA) + a.CenterRect(a);
		}

		for (auto& v : B) {
			v = Rotate(v - b.CenterRect(b), angleOfB) + b.CenterRect(b);
		}

		Point axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

		for (auto& axis : axes) {
			float P[4];

			for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

			float minA = *std::min_element(P, P + 4);
			float maxA = *std::max_element(P, P + 4);

			for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

			float minB = *std::min_element(P, P + 4);
			float maxB = *std::max_element(P, P + 4);

			if (maxA < minB || minA > maxB)
				return false;
		}

		return true;
	}

private:

	static inline float Mag(const Point& p) {
		return std::sqrt(p.GetXpoint() * p.GetXpoint() + p.GetYpoint() * p.GetYpoint());
	}

	static inline Point Norm(const Point& p) {
		return p * (1.f / Mag(p));
	}

	static inline float Dot(const Point& a, const Point& b) {
		return a.GetXpoint() * b.GetXpoint() + a.GetYpoint() * b.GetYpoint();
	}

	static inline Point Rotate(const Point& p, float angle) {
		float cs = std::cos(angle), sn = std::sin(angle);
		return Point(p.GetXpoint() * cs - p.GetYpoint() * sn, p.GetXpoint() * sn + p.GetYpoint() * cs);
	}
};
