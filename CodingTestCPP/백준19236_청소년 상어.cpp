// 백준 19236번 : 청소년 상어
// 조건
// 1. 칸
//  1-1. 4*4 칸에 각각 물고기가 속함
//  1-2. 각 물고기마다 1~16의 번호와, 8방향의 방향이 주어짐
// 2. 물고기 이동
//  2-1. 번호가 작은 물고기부터 순서대로 이동
//  2-2. 상어가 있는 칸은 이동 불가
//  2-3. 현재 방향으로 이동할 수 없는 경우 반시계 방향으로 45도로 회전시키며 이동가능 한 칸을 찾음
//       *없을 경우 정지.
//  2-4. 물고기가 존재하는 칸으로 이동할 때, 해당 위치의 물고기와 위치를 바꿈
// 3. 상어 이동
//  3-1. 최초 (0,0)위치의 물고기를 먹고 해당 칸에서 시작
//  3-2. 방향은 먹은 물고기의 방향을 따름
//  3-3. 해당 방향으로 여러개의 칸을 이동할 수 있고, 목적지 외의 경로상의 물고기는 먹지 않음
//  3-4. 이동할 수 있는 칸이 없다면 종료
// 4. 상어가 먹을 수 있는 물고기 번호의 합의 최댓값을 구하라
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int SHARK = -1, EMPTY = 0;

// 상, 좌상, 좌, 좌하, 하, 우하, 우, 우상
int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

struct Shark {
	int y, x, score, dir;
};

int ret = -1;

void MoveFish(vector<vector<pair<int, int>>>& board, vector<pair<int, int>>& fish) {
	for (int i = 1; i < fish.size(); i++) {
		auto p = fish[i];
		// 죽은 물고기
		if (board[p.first][p.second].first != i)
			continue;

		int dir = board[p.first][p.second].second;
		while (true) {
			int ny = p.first + dy[dir];
			int nx = p.second + dx[dir];
			// 위치 변경 
			if (0 <= ny && ny < 4 && 0 <= nx && nx < 4 && board[ny][nx].first != SHARK) {
				auto temp = board[ny][nx];
				board[ny][nx] = { i,dir };
				fish[i] = { ny,nx };

				board[p.first][p.second] = temp;
				fish[temp.first] = p;
				break;
			}

			// 회전 
			dir = (dir + 1) % 8;
			if (dir == board[p.first][p.second].second) {
				dir--;
				break;
			}
		}
	}
}

void solution(vector<vector<pair<int, int>>> board, vector<pair<int, int>> fish, Shark shark) {
	ret = max(ret, shark.score);
	MoveFish(board, fish);

	int ny = shark.y, nx = shark.x, dir = shark.dir;
	while (true) {
		ny += dy[dir];
		nx += dx[dir];
		if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4) break;
		if (board[ny][nx].first == EMPTY) continue;

		// 상태복사
		Shark nextShark = { ny,nx, shark.score + board[ny][nx].first, board[ny][nx].second };

		int num = board[ny][nx].first;
		board[shark.y][shark.x].first = EMPTY;
		board[ny][nx].first = SHARK;	// 이동

		solution(board, fish, nextShark);

		board[shark.y][shark.x].first = SHARK;
		board[ny][nx].first = num;
	}
}

int main() {
	vector<vector<pair<int, int>>> board(4, vector<pair<int, int>>(4));
	vector<pair<int, int>> fish(17);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			auto& p = board[y][x];
			cin >> p.first >> p.second;
			p.second = (p.second - 1) % 8; // 방향은 0-based
			fish[p.first] = { y,x };
		}
	}

	int score = board[0][0].first;
	int dir = board[0][0].second;
	board[0][0].first = SHARK;
	solution(board, fish, { 0, 0, score, dir });
	cout << ret << '\n';
	return 0;
}