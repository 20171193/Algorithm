// 백준 16932번 : 모양 만들기
// 조건 
// 1. 0과 1로 주어진 보드에서 0하나를 바꿔 
//    1의 인접 영역을 최대로 했을 때, 해당 영역의 크기
// 2. 2<=N,M<=1,000
// 풀이
// 1. 완탐 : 모든 0 하나씩 수정 후 BFS
//    불가 10^12(10^6 * 10^6)
// 2. 영역 구분 BFS + 이어질 수 있는 0만 확인
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, ret = -1, board[1001][1001], marked[1001][1001], areaCnt[500001];

int dc[4] = { 1, 0,-1,0 };
int dr[4] = { 0,1,0,-1 };
// BFS 영역 번호 마킹(marked), 영역 개수 카운팅(areaCnt)
void Marking(int sr, int sc, int mark) {
	int cnt = 1;

	queue<pair<int, int>> q;
	q.push({ sr,sc });
	marked[sr][sc] = mark;

	while (!q.empty()) {
		auto cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nr = dr[d] + cur.first;
			int nc = dc[d] + cur.second;

			if (nc < 0 || nc >= m || nr < 0 || nr >= n) continue;
			if (marked[nr][nc] || !board[nr][nc]) continue;

			marked[nr][nc] = mark;
			cnt++;
			q.push({ nr,nc });
		}
	}

	areaCnt[mark] = cnt;
	ret = max(ret, cnt);
}

void solution() {
	int mark = 1;
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			if (board[r][c] && !marked[r][c])
				Marking(r, c, mark++);
		}
	}

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			if (board[r][c]) continue;

			int used[4] = {};
			int usedCnt = 0;
			// 현재 칸 포함
			int cnt = 1;
			for (int d = 0; d < 4; d++) {
				int nr = dr[d] + r;
				int nc = dc[d] + c;
				if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
				if (!board[nr][nc]) continue;

				int num = marked[nr][nc];

				// 영역 중복확인
				bool isDup = false;
				for (int i = 0; i < usedCnt; i++) {
					if (used[i] == num) {
						isDup = true;
						break;
					}
				}
				if (isDup) continue;

				used[usedCnt++] = num;
				cnt += areaCnt[num];
			}

			ret = max(ret, cnt);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			cin >> board[r][c];

	solution();

	cout << ret << '\n';
	return 0;
}