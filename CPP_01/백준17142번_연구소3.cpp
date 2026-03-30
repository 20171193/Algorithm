// 백준 17142번 : 연구소 3(https://www.acmicpc.net/problem/17142)
// 조건
// 1. N*N 정사각형 (N<=50)
// 2. 빈칸(0), 벽(1), 바이러스(2) 
// 3. 바이러스 활성 시 1초만에 4방향 복제
// 4. 비활성 바이러스 M개를 활성 상태로 변경하려 함. (M<=10)
//  4-1. 활성 바이러스가 비활성 바이러스를 만나면 해당 바이러스를 활성상태로 변경
// 
// 풀이
// 1. BFS + 조합(10 c M)
// 2. N^2 * 252
//
// 시도
// 1. 50*50 최대 범위 계산 오류
#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>
using namespace std;

constexpr int INF = 2501;

int n, m, emptyCount, ret = INF, arr[51][51], visited[51][51];
vector<pair<int, int>> viruses;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

// bfs
int bfs(int bit) {
	int maxVisited = 1;
	int curEmptyCount = emptyCount;
	queue<pair<int, int>> q;
	for (int i = 0; i < viruses.size(); i++) {
		if (bit & (1 << i)) {
			q.push(viruses[i]);
			visited[viruses[i].first][viruses[i].second] = 1;
		}
	}

	bool clearFlag = false;
	while (!q.empty() && !clearFlag) {
		auto cur = q.front();
		q.pop();

		for (int d = 0; d < 4; d++) {
			int ny = dy[d] + cur.first;
			int nx = dx[d] + cur.second;
			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			if (arr[ny][nx] == 1) continue;
			int nVisit = visited[cur.first][cur.second] + 1;
			if (visited[ny][nx] && visited[ny][nx] <= nVisit) continue;


			if (arr[ny][nx] == 0) {
				--curEmptyCount;
				if (curEmptyCount == 0) {
					maxVisited = nVisit;
					clearFlag = true;
					break;
				}
			}

			q.push({ ny,nx });
			visited[ny][nx] = nVisit;
		}
	}

	memset(visited, 0, sizeof(visited));
	return curEmptyCount == 0 ? maxVisited - 1 : INF;
}

// 바이러스 조합(10cM)
void solution(int cur, int depth, int bit) {
	if (viruses.size() - (cur + 1) < m - depth) return;
	if (depth == m) {
		ret = min(ret, bfs(bit));
		return;
	}
	for (int i = cur + 1; i < viruses.size(); i++) {
		if (bit & (1 << i)) continue;

		solution(i, depth + 1, bit | (1 << i));
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == 2)
				viruses.push_back({ i,j });
			else if (arr[i][j] == 0)
				emptyCount++;
		}
	}

	solution(-1, 0, 0);

	if (ret == INF) cout << -1 << '\n';
	else cout << ret << '\n';
	return 0;
}