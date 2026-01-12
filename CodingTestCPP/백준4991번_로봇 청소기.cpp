// 백준 4991번 : 로봇 청소기 (https://www.acmicpc.net/problem/4991)
// 조건
// 1. h*w(w,h<=20)
// 2. 깨끗한 칸(.), 더러운 칸(*), 가구(x), 로봇 청소기(o)
// 3. 더러운 칸을 모두 깨끗한 칸으로 바꾸는 이동 횟수의 최솟값
// 4. 더러운 칸의 개수는 10개 이하
//
// 풀이
// 1. bfs + 비트마스킹 방문체크
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <string>
#include <climits>
using namespace std;

int w, h, dirtyCount, visited[21][21][1 << 10], dirtyID[21][21];
pair<int, int> robot;
char board[21][21];

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

struct Node { int y, x, mask; };

int solution() {
	int answer = INT_MAX;
	// 종료 마스크 : 더러운 칸의 모든 비트가 켜진 경우
	int endMask = (1 << dirtyCount) - 1;

	queue<Node> q;
	q.push({ robot.first, robot.second, 0 });

	while (!q.empty()) {
		auto cur = q.front(); q.pop();

		if (cur.mask == endMask) {
			answer = visited[cur.y][cur.x][cur.mask];
			break;
		}

		for (int d = 0; d < 4; d++) {
			int ny = cur.y + dy[d];
			int nx = cur.x + dx[d];
			if (ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
			if (board[ny][nx] == 'x') continue;

			int nMask = cur.mask;
			if (board[ny][nx] == '*') nMask |= (1 << dirtyID[ny][nx]);
			if (visited[ny][nx][nMask]) continue;

			visited[ny][nx][nMask] = visited[cur.y][cur.x][cur.mask] + 1;
			q.push({ ny,nx,nMask });
		}
	}

	memset(visited, 0, sizeof(visited));
	return answer == INT_MAX ? -1 : answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	vector<int> answer;

	while (true) {
		cin >> w >> h;
		if (w == 0 && h == 0) break;

		dirtyCount = 0;
		for (int i = 0; i < h; i++) {
			string temp;
			cin >> temp;
			for (int j = 0; j < w; j++) {
				board[i][j] = temp[j];
				if (temp[j] == 'o')
					robot = { i,j };
				if (temp[j] == '*')
					dirtyID[i][j] = dirtyCount++;
			}
		}

		answer.push_back(solution());
	}

	for (int ans : answer)
		cout << ans << '\n';

	return 0;
}