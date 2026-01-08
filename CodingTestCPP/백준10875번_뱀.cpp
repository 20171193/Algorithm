// 백준 10875번 : 뱀(https://www.acmicpc.net/problem/10875)
// 조건
// 1. 보드 (2L+1)*(2L+1) : (L<=10^8) 
// 2. 회전 M(1<=1000)
// 3. 시간 T(1<=2*10^8) 
// 
// 풀이
// 1. 배열 방문체크는 불가 
// 2. 한번 회전할 때마다 dir * time의 벡 생성
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;

int l, n, dir;
ll curTime = 0;
pair<ll, ll> curPos = { 0,0 };
pair<ll, char> inputs[1001];

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0, 1 };

struct Segment {
	ll y1, x1, y2, x2;
	Segment() : y1(0), x1(0), y2(0), x2(0) {}
	Segment(ll y1, ll x1, ll y2, ll x2) : y1(y1), x1(x1), y2(y2), x2(x2) {}
	bool isHorizontal() const {
		return y1 == y2;
	}
	bool isVertical() const {
		return x1 == x2;
	}
	pair<ll, ll> GetIntersection(const Segment& other) const {
		pair<ll, ll> intersection = { LLONG_MAX, LLONG_MAX };

		// 가로-세로
		if (isHorizontal() && other.isVertical()) {
			if (min(x1, x2) <= other.x1 && other.x1 <= max(x1, x2)
				&& min(other.y1, other.y2) <= y1 && y1 <= max(other.y1, other.y2))
				intersection = { y1, other.x1 };
		}
		else if (isVertical() && other.isHorizontal()) {
			if (min(other.x1, other.x2) <= x1 && x1 <= max(other.x1, other.x2)
				&& min(y1, y2) <= other.y1 && other.y1 <= max(y1, y2))
				intersection = { other.y1, x1 };
		}
		// 가로-가로
		else if (isHorizontal() && other.isHorizontal()) {
			if (y1 == other.y1) {
				ll left = min(x1, x2);
				ll right = max(x1, x2);
				// 좌측 방향 이동에서 접한 경우
				if (other.x1 <= right)
					intersection = { y1, right };
				// 우측 방향 이동에서 접한 경우
				if (other.x2 >= left)
					intersection = { y1, left };
			}
		}
		// 세로-세로
		else if (isVertical() && other.isVertical()) {
			if (x1 == other.x1) {
				ll top = min(y1, y2);
				ll bottom = max(y1, y2);
				// 아랫 방향 이동에서 접한 경우
				if (other.y2 >= top)
					intersection = { top, x1 };
				// 윗 방향 이동에서 접한 경우
				if (other.y1 <= bottom)
					intersection = { bottom, x1 };
			}
		}

		return intersection;
	}
};

Segment Move(const pair<ll, char>& input) {
	pair<ll, ll> nextPos = { 0,0 };
	nextPos.first = curPos.first + dy[dir] * input.first;
	nextPos.second = curPos.second + dx[dir] * input.first;

	Segment seg(curPos.first, curPos.second, nextPos.first, nextPos.second);

	// 방향 전환 및 시간 누적
	dir = input.second == 'L' ? (dir == 0 ? 3 : dir - 1) : (dir == 3 ? 0 : dir + 1);
	curTime += input.first;
	curPos = nextPos;

	return seg;
}

ll solution() {
	// 4모퉁이 추가
	int totalSegments = n + 4;
	vector<Segment> segments(totalSegments);
	segments[0] = Segment(l, -l, l, l), segments[1] = Segment(l, -l, -l, -l);
	segments[2] = Segment(l, l, -l, l), segments[3] = Segment(-l, -l, -l, l);

	pair<ll, ll> notIntersectFlag = { LLONG_MAX, LLONG_MAX };

	for (int i = 4; i < totalSegments; i++) {
		// 이동 및 직선 생성
		segments[i] = Move(inputs[i - 4]);

		for (int j = 0; j < i; j++) {
			pair<ll, ll> intersection = segments[j].GetIntersection(segments[i]);
			if (intersection == notIntersectFlag) continue;

			// 겹치는 구간 만큼 현재 시간에서 빼기 (통과한 경우) 
			ll overlapDistance = abs(segments[i].y1 - intersection.first)
				+ abs(segments[i].x1 - intersection.second);

			return curTime - overlapDistance;
		}
	}
	return curTime;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> l >> n;
	for (int i = 0; i < n; i++)
		cin >> inputs[i].first >> inputs[i].second;

	cout << solution() << '\n';
	return 0;
}