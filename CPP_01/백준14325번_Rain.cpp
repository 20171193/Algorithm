// 백준 14324번 : Rain(https://www.acmicpc.net/problem/14325)
// 조건
// 1. 물이 더 이상 차오르지 않을 때까지 비가 왔을 때 총 물의 부피
//  1-1. 끝부분은 흘러내림
// 
// 풀이
// 1. 맵의 가장자리부터 다익스트라
// 2. 다익스트라
//  2-1. 영역의 끝 부분이 가장 낮은 높이임을 보장  
//  2-2. 작은 요소 우선 탐색
//     1. 내부로 탐색 (가장자리->가장자리 배제)
//     2. 작은 경우 이전 요소로 채우고 할당 (+카운팅)
//     3. 큰 경우 그대로 할당
//
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory>
using namespace std;

int t, r, c, arr[51][51];
bool visited[51][51];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

struct Node {
	int y, x, height;
	bool operator<(const Node& other) const {
		return height > other.height;
	}
};

int solution()
{
	int water = 0;

	priority_queue<Node> pq;

	// 맵 가장자리 할당
	for (int i = 0; i < r; i++) {
		pq.push({ i, 0, arr[i][0] });
		visited[i][0] = true;
		pq.push({ i, c - 1, arr[i][c - 1] });
		visited[i][c - 1] = true;
	}
	for (int i = 1; i < c - 1; i++) {
		pq.push({ 0, i, arr[0][i] });
		visited[0][i] = true;
		pq.push({ r - 1, i, arr[r - 1][i] });
		visited[r - 1][i] = true;
	}

	while (!pq.empty()) {
		auto cur = pq.top();
		pq.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			int nHeight = arr[ny][nx];
			// 범위 제한
			if (ny < 0 || ny >= r || nx < 0 || nx >= c) continue;
			if (visited[ny][nx]) continue;

			if (nHeight < cur.height) {
				int diff = cur.height - nHeight;
				water += diff;

				nHeight = cur.height;
			}

			pq.push({ ny,nx, nHeight });
			visited[ny][nx] = true;
		}
	}

	return water;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	vector<string> answer(t);

	int caseCount = 1;
	while (t--) {
		cin >> r >> c;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				cin >> arr[i][j];

		memset(visited, false, sizeof(visited));

		answer[caseCount - 1] = "Case #" + to_string(caseCount) + ": " + to_string(solution());
		caseCount++;
	}

	for (auto& ans : answer)
		cout << ans << '\n';
	return 0;
}