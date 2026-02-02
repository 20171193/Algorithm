// 백준 20149번 : 선분 교차 3(https://www.acmicpc.net/problem/20149)
// 조건
// 1. 2차원 두 선분의 교차
// 2. -10^6 <= x,y <= 10^6
// 3. 절대/상대 오차는 10^-9까지 허용
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cfloat>
using namespace std;

typedef long double ld;

struct Segment {
	ld x1, y1, x2, y2;
	ld vx() const { return x2 - x1; }
	ld vy() const { return y2 - y1; }
	ld mnx() const { return min(x1, x2); }
	ld mxx() const { return max(x1, x2); }
	ld mny() const { return min(y1, y2); }
	ld mxy() const { return max(y1, y2); }
	bool isPoint() const { return x1 == x2 && y1 == y2; }
};

Segment seg1, seg2;
ld px = LDBL_MAX, py = LDBL_MAX;

ld cross(ld vx1, ld vy1, ld vx2, ld vy2) {
	return vx1 * vy2 - vx2 * vy1;
}

bool solution() {
	ld d123 = cross(seg1.vx(), seg1.vy(), seg2.x1 - seg1.x1, seg2.y1 - seg1.y1);
	ld d124 = cross(seg1.vx(), seg1.vy(), seg2.x2 - seg1.x1, seg2.y2 - seg1.y1);
	if (d123 * d124 > 0)
		return false;

	ld mnx1 = seg1.mnx(), mny1 = seg1.mny(), mxx1 = seg1.mxx(), mxy1 = seg1.mxy();
	ld mnx2 = seg2.mnx(), mny2 = seg2.mny(), mxx2 = seg2.mxx(), mxy2 = seg2.mxy();

	// 포함 확인
	if (d123 == 0 || d124 == 0) {
		// 두 선분이 동일 선상에 위치하는 경우
		if (d123 == d124) {
			pair<ld, ld> p1 = { seg1.x1, seg1.y1 }, p2 = { seg1.x2, seg1.y2 };
			pair<ld, ld> p3 = { seg2.x1, seg2.y1 }, p4 = { seg2.x2, seg2.y2 };
			// 직선 상 정렬
			if (p1 > p2) swap(p1, p2);
			if (p3 > p4) swap(p3, p4);

			if (p1 <= p4 && p3 <= p2) {
				// 끝점에서 겹치는 경우만 할당
				if (p2 == p3) {
					px = p2.first;
					py = p2.second;
				}
				else if (p1 == p4) {
					px = p1.first;
					py = p1.second;
				}
				return true;
			}
		}
		// 한 점에서 만나는 경우
		else {
			if (d123 == 0 && (mnx1 <= seg2.x1 && seg2.x1 <= mxx1 && mny1 <= seg2.y1 && seg2.y1 <= mxy1)) {
				px = seg2.x1;
				py = seg2.y1;
				return true;
			}
			else if (d124 == 0 && (mnx1 <= seg2.x2 && seg2.x2 <= mxx1 && mny1 <= seg2.y2 && seg2.y2 <= mxy1)) {
				px = seg2.x2;
				py = seg2.y2;
				return true;
			}
		}
	}
	// 교차 확인
	else {
		ld d341 = cross(seg2.vx(), seg2.vy(), seg1.x1 - seg2.x1, seg1.y1 - seg2.y1);
		ld d342 = cross(seg2.vx(), seg2.vy(), seg1.x2 - seg2.x1, seg1.y2 - seg2.y1);
		if (d341 * d342 > 0) return false;

		// 한쪽만 접하는 게 보장됨
		if (d341 * d342 == 0) {
			if (d341 == 0 && (mnx2 <= seg1.x1 && seg1.x1 <= mxx2 && mny2 <= seg1.y1 && seg1.y1 <= mxy2)) {
				px = seg1.x1;
				py = seg1.y1;
				return true;
			}
			else if (d342 == 0 && (mnx2 <= seg1.x2 && seg1.x2 <= mxx2 && mny2 <= seg1.y2 && seg1.y2 <= mxy2)) {
				px = seg1.x2;
				py = seg1.y2;
				return true;
			}
		}
		else {
			// 외적 비로 교차점 찾기
			ld ratio = abs(d123) / (abs(d123) + abs(d124));
			px = seg2.x1 + seg2.vx() * ratio;
			py = seg2.y1 + seg2.vy() * ratio;
			return true;
		}
	}

	return false;
}

int main() {
	cin >> seg1.x1 >> seg1.y1 >> seg1.x2 >> seg1.y2
		>> seg2.x1 >> seg2.y1 >> seg2.x2 >> seg2.y2;

	if (solution()) {
		cout << 1 << '\n';

		if (px != LDBL_MAX && py != LDBL_MAX)
			cout << fixed << setprecision(11) << px << ' ' << py << '\n';
	}
	else
		cout << 0 << '\n';
	return 0;
}