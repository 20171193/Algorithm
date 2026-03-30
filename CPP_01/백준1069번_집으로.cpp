// 백준 1069번 : 집으로
// 조건
// 1. (x,y) -> (0,0)
//  1-1. 걷기 : 1초에 1만큼 이동
//  1-2. 점프 : T초에 D만큼 이동
// 2. 집에 돌아오는 데 걸리는 시간의 최솟값
// 3. (1<=X,Y<=1,000), (1<=D,T<=10,000)
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

typedef long double ld;

int x, y, d, t;

ld magnitude(int x, int y) {
	return sqrt((ld)x * x + (ld)y * y);
}

ld solution() {
	ld totalTime = 0;
	ld dist = magnitude(x, y);

	int jumpCnt = 0;
	if (d <= t) return dist; // 걷는게 더 빠른 경우
	jumpCnt = (int)dist / d;

	if (jumpCnt >= 1) {
		dist -= (jumpCnt - 1) * d;	// 점프로 이동
		totalTime += (jumpCnt - 1) * t;

		// d <= dist <= 2d
		totalTime += min({ld(dist - d + t), (ld)t * 2 });
	}
	else
		totalTime += min({ dist, (ld)(d - dist + t), (ld)t * 2 });
	return totalTime;
}

int main() {
	cin >> x >> y >> d >> t;

	cout.precision(10);
	cout << fixed << solution() << '\n';
	return 0;
}