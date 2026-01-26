// 백준 10255번 : 교차점(https://www.acmicpc.net/problem/10255)
// 조건
// 1. 사각형 최대 범위 (-10,000 <= x,y <=10,000)
// 2. 교차점의 개수가 유한할 경우 교차점 개수, 무한히 많을 땐 4 출력
// 풀이
// 1. 선분의 교차
// 2. 범위판단
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int t;

struct Segment {
	int x1, y1, x2, y2;
	Segment() {}
	Segment(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};
struct Rectangle {
	Segment segments[4];
	Rectangle() {}
	Rectangle(int mnx, int mny, int mxx, int mxy) {
		segments[0] = Segment(mnx, mny, mxx, mny);
		segments[1] = Segment(mnx, mxy, mxx, mxy);
		segments[2] = Segment(mnx, mny, mnx, mxy);
		segments[3] = Segment(mxx, mny, mxx, mxy);
	}
};

float Cross(const Segment& seg, int px, int py) {
	return (seg.x2 - seg.x1) * (py - seg.y1) - (seg.y2 - seg.y1) * (px - seg.x1);
}

int solution(const Rectangle& rect, const Segment& seg) {
	int itcCount = 0;

	// 교점이 꼭짓점에 존재할 경우
	bool intersectVertex = false;
	for (const auto& side : rect.segments) {
		float d1 = Cross(side, seg.x1, seg.y1);
		float d2 = Cross(side, seg.x2, seg.y2);

		if (d1 * d2 > 0) continue;
		else if (d1 * d2 == 0) {
			int mnx = min(side.x1, side.x2);
			int mxx = max(side.x1, side.x2);
			int mny = min(side.y1, side.y2);
			int mxy = max(side.y1, side.y2);

			// 평행한 경우
			if (d1 == 0 && d2 == 0) {

			}
			// 한 점이 포함된 경우
			else if (d1 == 0) {
				if (mnx <= seg.x1 && seg.x1 <= mxx && mny <= seg.y1 && seg.y1 <= mxy) {
					// 꼭짓점에서 만난 경우
					if ((seg.x1 == side.x1 && seg.y1 == side.y1) || (seg.x1 == side.x2 && seg.y1 == side.y2)) {
						// 같은 꼭짓점 한 번만 카운팅
						if (intersectVertex) continue;
						intersectVertex = true;
					}
					itcCount++;
				}
			}
			else /* d2 == 0 */ {
				if (mnx <= seg.x2 && seg.x2 <= mxx && mny <= seg.y2 && seg.y2 <= mxy) {
					// 꼭짓점에서 만난 경우
					if ((seg.x2 == side.x1 && seg.y2 == side.y1) || (seg.x2 == side.x2 && seg.y2 == side.y2)) {
						// 같은 꼭짓점 한 번만 카운팅
						if (intersectVertex) continue;
						intersectVertex = true;
					}
					itcCount++;
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> t;

	vector<int> answer(t);
	int idx = 0;
	while (t--) {
		// 사각형 할당
		int mnx, mny, mxx, mxy;
		cin >> mnx >> mny >> mxx >> mxy;
		Rectangle rect(mnx, mny, mxx, mxy);

		// 선분 할당
		Segment seg;
		cin >> seg.x1 >> seg.y1 >> seg.x2 >> seg.y2;

		answer[idx++] = solution(rect, seg);
	}

	for (int ans : answer)
		cout << ans << '\n';

	return 0;
}