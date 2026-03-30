// 백준17837번 : 새로운 게임 2
// 조건
// 1. 턴
//  1-1. 1~K번 말을 순서대로 이동
//  1-2. 이동하는 칸에 말이 존재하면, 현재 말을 해당 말 위에 쌓음.
// 2. 칸
//  2-1. 빨간색 : 이동하는 말의 순서를 역순으로 변경
//  2-2. 파란색/범위밖 : 이동 방향을 반대로하고 한 칸 이동
//                     : 반대 방향도 마찬가지라면 정지
// 3. 말이 4개 이상 쌓이는 순간 게임 종료
// 4. 게임이 종료되는 턴의 번호를 출력 (1,000이상이거나 게임이 종료되지 않는 경우 -1출력)
//
// 풀이
// 1. 턴 진행 시뮬레이션
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int WHITE = 0, RED = 1, BLUE = 2;

struct Piece {
	int y, x, d;
};

int n, k, board_cell[13][13];
vector<int> board[13][13];
Piece pieces[11];

int dx[5] = { 0, 1,-1,0,0 };
int dy[5] = { 0, 0,0,-1,1 };

int Flip(int dir) {
	if (dir == 1) return 2;
	if (dir == 2) return 1;
	if (dir == 3) return 4;
	else return 3;
}

int solution() {
	for (int turn = 1; turn <= 1000; turn++) {
		for (int i = 1; i <= k; i++) {
			auto& piece = pieces[i];
			int ny = piece.y + dy[piece.d];
			int nx = piece.x + dx[piece.d];

			// 파란칸/범위밖 : 방향 반전
			if (ny < 1 || ny > n || nx < 1 || nx > n || board_cell[ny][nx] == BLUE) {
				piece.d = Flip(piece.d);
				ny = piece.y + dy[piece.d];
				nx = piece.x + dx[piece.d];
			}

			// 다시 파란칸/범위밖일 경우 continue
			if (ny < 1 || ny > n || nx < 1 || nx > n || board_cell[ny][nx] == BLUE) continue;
			else {
				vector<int>& curStack = board[piece.y][piece.x];
				int order = find(curStack.begin(), curStack.end(), i) - curStack.begin();
				// 탑 분리
				vector<int> moveStack(curStack.begin() + order, curStack.end());
				for (int num : moveStack) {
					pieces[num].y = ny;
					pieces[num].x = nx;
				}

				curStack.erase(curStack.begin() + order, curStack.end());

				// 빨간칸 : 이동할 탑 반전
				if (board_cell[ny][nx] == RED)
					reverse(moveStack.begin(), moveStack.end());

				// 탑 이동
				board[ny][nx].insert(board[ny][nx].end(), moveStack.begin(), moveStack.end());

				if (board[ny][nx].size() >= 4) return turn;
			}
		}
	}
	return -1;
}

int main() {
	cin >> n >> k;
	// 1-based
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= n; c++)
			cin >> board_cell[r][c];

	for (int i = 1; i <= k; i++) {
		int y, x, d;
		cin >> y >> x >> d;
		pieces[i] = { y,x,d };
		board[y][x].push_back(i);
	}

	cout << solution() << '\n';
	return 0;
}