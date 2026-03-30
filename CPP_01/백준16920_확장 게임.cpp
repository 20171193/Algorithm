// 백준 16920번 : 확장 게임
// 조건
// 1. 보드 N*M(1<=N,M<=10^3)
// 2. 플레이어 P(1<=P<=9)
// 3. 이동 거리 S(1<=S<=10^9)
// 풀이
// 1. S만큼 확장 (BFS)
#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;

int n, m, p, dists[10], result[10];
char board[1001][1001];

queue<pair<int, int>> numQ[10];

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

void solution() {
	bool flag = true;

	// 번호별 최초 영역 할당
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c = board[i][j];
			if (c >= '1' && c <= '9') {
				numQ[c - '0'].push({ i,j });
				result[c - '0']++;
			}
		}
	}

	while (flag) {
		flag = false;
		// 영역 확장
		for (int i = 1; i <= p; i++) {
			for (int dist = 0; dist < dists[i]; dist++) {
				int size = numQ[i].size();
				if (size == 0) break;

				while (size--) {
					auto cur = numQ[i].front();
					numQ[i].pop();

					for (int d = 0; d < 4; d++) {
						int ny = dy[d] + cur.first;
						int nx = dx[d] + cur.second;
						if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
						if (board[ny][nx] != '.') continue;

						board[ny][nx] = i + '0';	// 영역 확장
						numQ[i].push({ ny,nx });

						result[i]++;	// 영역 카운팅
						flag = true;	// 확장 성공 플래그
					}
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> p;
	for (int i = 1; i <= p; i++)
		cin >> dists[i];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> board[i][j];

	solution();

	for (int i = 1; i <= p; i++)
		cout << result[i] << ' ';
	cout << '\n';
	return 0;
}