// 백준 17071번 : 숨바꼭질 5 (https://www.acmicpc.net/problem/17071)
// 조건
// 1. 수빈이 위치 N(0<=N<=500,000)
// 2. 동생 위치 K(0<=K<=500,000)
// 3. 수빈이의 이동은 1초가 걸림
//  3-1. (N-1), (N+1), (2*N)
// 4. 동생은 매 초마다 지난 시간만큼 이동
//  4-1. f(1) = K+1
//  4-2. f(2) = f(1) + 2
// 
// 풀이
// 1. 상태 bfs
//  1-1. 2차원 배열 불가(500,000*500,000)
//  1-2. n초 후 수빈이 위치로 할당. (n초 후 동생의 위치는 매 번 동일) 
//  1-3. 2t초 후 위치는 현재 위치일 수 있음. 이동 방향 왔다 갔다
//   - 짝/홀수 시간에 대한 최소 시간만 기록 
//   - 같은 짝/홀수 시간대에 수빈이가 먼저/동시에 도착한 경우 성공   
// 2. 시간 예상
//  2-1. 수빈이 bfs 약 300만 (3방향 * 100만 방문상태(짝/홀 2 * 최대 좌표 500,000))
//  2-2. 동생 반복 약 1000 ( n*(n+1)/2 = 500,000, n은 약 1000 즉, 최대 1000초 정도)
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

int n, k, visited[2][500001];

int Move(int pos, int type) {
	if (type == 0) return pos - 1;
	if (type == 1) return pos + 1;
	return pos * 2;
}

int solution() {
	// n*(n-1)/2 = 500,000, n은 999~1000
	int answer = 1001;

	// 방문배열 초ㄱ기화
	memset(visited, -1, sizeof(visited));

	// 수빈이 위치 시뮬레이션
	// <초, 위치>
	queue<pair<int, int>> q;
	q.push({ 0, n });
	visited[0][n] = 0;

	while (!q.empty()) {
		auto cur = q.front(); q.pop();

		int nextTime = cur.first + 1;
		int timeIndex = nextTime % 2;
		for (int nextPos : {cur.second - 1, cur.second + 1, cur.second * 2}) {
			if (nextPos < 0 || nextPos > 500000) continue;

			if (visited[timeIndex][nextPos] == -1) {
				visited[timeIndex][nextPos] = nextTime;
				q.push({ nextTime, nextPos });
			}
		}
	}

	// 동생 위치 시뮬레이션
	int targetPos = k;
	for (int t = 0; targetPos < 500001; targetPos += ++t) {
		int timeIndex = t % 2;
		// 이미 같은 홀/짝에 도착한 경우 (왔다갔다 반복)
		if (visited[timeIndex][targetPos] != -1
			&& visited[timeIndex][targetPos] <= t)
			return t;
	}

	return -1;
}

int main() {
	cin >> n >> k;
	cout << solution() << '\n';
	return 0;
}