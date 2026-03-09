// 백준 1938번 : 통나무 옮기기
// 조건
// 1. 통나무(BBB)를 움직여 목표 지점(EEE)에 위치 
// 2. 옵션 : 5개
//  2-1. 이동 : 상/하/좌/우
//  2-2. 회전 : 중심점을 중심으로 90도 회전(항상 통나무의 길이는 3)
//            : 중심에서 3*3 영역에 다른 나무(1)가 존재하면 안됨
// 풀이
// 1. BFS + 상태 메모이제이션
#include <iostream>
#include <queue>
#include <string>
using namespace std;

// D,U,R,L
int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };

int n, visited[2][51][51];
string board[51];

struct State {
	bool isHorizontal;
	int cy, cx;

	State(bool isHorizontal, int cy, int cx) : isHorizontal(isHorizontal), cy(cy), cx(cx) {}
};
bool InBound(int y, int x) {
	return 0 <= y && y < n && 0 <= x && x < n;
}
bool CanPlace(const State& state) {
	if (state.isHorizontal) {
		for (int dx = -1; dx <= 1; dx++) {
			int ny = state.cy;
			int nx = state.cx + dx;
			if (!InBound(ny, nx) || board[ny][nx] == '1') return false;
		}
	}
	else {
		for (int dy = -1; dy <= 1; dy++) {
			int ny = state.cy + dy;
			int nx = state.cx;
			if (!InBound(ny, nx) || board[ny][nx] == '1') return false;
		}
	}
	return true;
}
bool CanRotate(const State& state) {
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			int ny = state.cy + dy;
			int nx = state.cx + dx;
			if (!InBound(ny, nx) || board[ny][nx] == '1') return false;
		}
	}
	return true;
}
bool ProcessOper(int oper, State& state) {
	if (oper < 4) {
		state.cy += dy[oper];
		state.cx += dx[oper];
		return CanPlace(state);
	}
	else {
		if (!CanRotate(state)) return false;
		state.isHorizontal = !state.isHorizontal;
		return true;
	}
}

int solution() {
	// 시작지, 목적지 할당
	State start(0, -1, -1), end(0, -1, -1);
	bool findFlag = false;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (board[y][x] == 'B' && start.cx == -1) {
				if (y + 2 < n && board[y + 1][x] == 'B' && board[y + 2][x] == 'B') {
					start.isHorizontal = false;
					start.cx = x;
					start.cy = y + 1;
				}
				else if (x + 2 < n && board[y][x + 1] == 'B' && board[y][x + 2] == 'B') {
					start.isHorizontal = true;
					start.cx = x + 1;
					start.cy = y;
					x += 2;
				}
			}
			if (board[y][x] == 'E' && end.cx == -1) {
				if (y + 2 < n && board[y + 1][x] == 'E' && board[y + 2][x] == 'E') {
					end.isHorizontal = false;
					end.cx = x;
					end.cy = y + 1;
				}
				else if (x + 2 < n && board[y][x + 1] == 'E' && board[y][x + 2] == 'E') {
					end.isHorizontal = true;
					end.cx = x + 1;
					end.cy = y;
					x += 2;
				}

			}

			if (start.cx != -1 && end.cx != -1) {
				findFlag = true;
				break;
			}
		}
		if (findFlag) break;
	}

	// BFS
	queue<State> q;
	q.push(start);
	visited[start.isHorizontal][start.cy][start.cx] = 1;

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();

		for (int oper = 0; oper < 5; oper++) {
			State next = cur;
			if (!ProcessOper(oper, next)) continue;
			if (visited[next.isHorizontal][next.cy][next.cx]) continue;

			visited[next.isHorizontal][next.cy][next.cx] = visited[cur.isHorizontal][cur.cy][cur.cx] + 1;
			q.push(next);
		}
	}

	int ret = visited[end.isHorizontal][end.cy][end.cx];

	if (ret == 0)
		return ret;
	else
		return ret - 1;	// 방문 체크를 1로 시작
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> board[i];

	cout << solution() << '\n';
	return 0;
}