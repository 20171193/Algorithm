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
#include <set>
using namespace std;

typedef long long ll;
typedef long double ld;

constexpr int INF = 4;

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

ll Cross(const Segment& seg, int px, int py) {
	return (ll)(seg.x2 - seg.x1) * (py - seg.y1) - (ll)(seg.y2 - seg.y1) * (px - seg.x1);
}

// 4, 7
int solution(const Rectangle& rect, const Segment& seg) {
	// 교점좌표 할당
	set<pair<ld, ld>> intersection;

	for (const auto& side : rect.segments) {
		ll d1 = Cross(side, seg.x1, seg.y1);
		ll d2 = Cross(side, seg.x2, seg.y2);

		// 교점이 없는 경우
		if (d1 * d2 > 0)
			continue;

		int mnx = min(side.x1, side.x2);
		int mxx = max(side.x1, side.x2);
		int mny = min(side.y1, side.y2);
		int mxy = max(side.y1, side.y2);

		// 포함 확인
		if (d1 * d2 == 0) {
			if (d1 == 0 && d2 == 0) {
				bool isHorizontal = mny == mxy;
				// 꼭짓점에서 접하는 경우 or 일부가 포함되는 경우
				// 무조건 리턴되는 부분 (0 or 1 or INF(4))
				if (isHorizontal && mny == seg.y1) {
					int mnsx = min(seg.x1, seg.x2);
					int mxsx = max(seg.x1, seg.x2);
					// 선분의 일부가 변에 포함되는 경우
					if ((mnx < mnsx && mnsx < mxx) || (mnx < mxsx && mxsx < mxx))
						return mnsx == mxsx ? 1 : INF;	// 주어진 선분이 점인 경우 예외
					// 선분이 변을 포함하는 경우
					else if (mnsx <= mnx && mxsx >= mxx)
						return INF;
					// 꼭짓점에서만 접하는 경우
					else if (mnx == mxsx || mxx == mnsx)
						return 1;
					// 아예 접하지 않는 경우
					else
						return 0;
				}
				else if (!isHorizontal && mnx == seg.x1) {
					int mnsy = min(seg.y1, seg.y2);
					int mxsy = max(seg.y1, seg.y2);

					// 선분의 일부가 변에 포함되는 경우
					if ((mny < mnsy && mnsy < mxy) || (mny < mxsy && mxsy < mxy))
						return mnsy == mxsy ? 1 : INF;	// 주어진 선분이 점인 경우 예외
					// 선분이 변을 포함하는 경우
					else if (mnsy <= mny && mxsy >= mxy)
						return INF;
					// 꼭짓점에서만 접하는 경우
					else if (mny == mxsy || mxy == mnsy)
						return 1;
					// 아예 접하지 않는 경우
					else
						return 0;
				}
			}
			// 선분의 한 점이 포함된 경우
			else if (d1 == 0) {
				if (mnx <= seg.x1 && seg.x1 <= mxx && mny <= seg.y1 && seg.y1 <= mxy)
					intersection.insert({ (ld)seg.x1, (ld)seg.y1 });
			}
			else /* d2 == 0 */ {
				if (mnx <= seg.x2 && seg.x2 <= mxx && mny <= seg.y2 && seg.y2 <= mxy)
					intersection.insert({ (ld)seg.x2, (ld)seg.y2 });
			}
		}
		// 교차 확인
		else {
			ll d3 = Cross(seg, side.x1, side.y1);
			ll d4 = Cross(seg, side.x2, side.y2);
			if (d3 * d4 > 0) continue;
			else if (d3 * d4 < 0) {
				// 외적 비
				ld ratio = (ld)abs(d1) / (abs(d1) + abs(d2));
				ld px = seg.x1 + (seg.x2 - seg.x1) * ratio;
				ld py = seg.y1 + (seg.y2 - seg.y1) * ratio;
				intersection.insert({ px, py });
			}
			else if (d3 != d4) {
				intersection.insert({ d3 == 0 ? (ld)side.x1 : (ld)side.x2
					, d3 == 0 ? (ld)side.y1 : (ld)side.y2 });
			}
		}
	}

	return intersection.size();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int t;
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