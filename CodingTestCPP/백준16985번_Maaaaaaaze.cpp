// 백준 16985번 : Ma..aze(https://www.acmicpc.net/problem/16985)
// 조건
// 1. 흰 칸은 들어갈 수 있는 칸.
// 2. 판을 시계, 반시계로 회전가능
// 3. 판을 쌓아 만들어진 정육면체에서 탈출
// 풀이
// 1. 완탐 
//  1-1. 판 순서(5!) * 방향(4^5) 
// 2. 각 보드 비트마스킹 (5*5 = 25)
#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>
#include <algorithm>
using namespace std;

constexpr int BOARD_SIZE = 5, INF = BOARD_SIZE * BOARD_SIZE * BOARD_SIZE + BOARD_SIZE;
int board[5][4], visited[5][5][5];
int answer = INF;
// dfs 전역
bool choosed[5];
int order[5], rotation[5], tower[5];

struct vector3 {
	int z, y, x;
	vector3(int z, int y, int x) : z(z), y(y), x(x) {}
	vector3 operator+(const vector3& other) const {
		return { z + other.z, y + other.y, x + other.x };
	}
	bool operator==(const vector3& other) const {
		return z == other.z && y == other.y && x == other.x;
	}
	bool isinbound() {
		return z >= 0 && z < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && x >= 0 && x < BOARD_SIZE;
	}
};

vector3 dir[6] = { {1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1} };

// 대략  < 100,000,000(1억)
// 3. 최종 보드 BFS : (5*5*5)*6 = 125*6 = 750
void solveBFS() {
	memset(visited, 0, sizeof(visited));
	vector3 target = { 4,4,4 };

	queue<vector3> q;
	visited[0][0][0] = 1;
	q.push({ 0,0,0 });

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();

		if (answer <= visited[cur.z][cur.y][cur.x]) continue;
		int curVisit = visited[cur.z][cur.y][cur.x];

		for (int d = 0; d < 6; d++)
		{
			auto next = cur + dir[d];
			// 범위 제한
			if (!next.isinbound()) continue;
			// 이동 불가능
			if (!(tower[next.z] & (1 << (next.y * BOARD_SIZE + next.x)))) continue;

			// 방문/거리 확인
			int& refNextVisit = visited[next.z][next.y][next.x];
			if (refNextVisit && refNextVisit <= curVisit + 1) continue;

			// 방문 체크
			refNextVisit = curVisit + 1;

			if (next == target)
				answer = min(answer, refNextVisit - 1);
			else
				q.push(next);
		}
	}
}
// 2. 배치된 보드 회전 (중복 순열) : 4^5 = 2^10 = 1024
void solveRotation(int depth) {
	if (depth == 5) {
		// 시작위치, 도착위치 모두 on 인 경우만 실행
		if (!(board[order[0]][rotation[0]] & (1 << 0)) || !(board[order[4]][rotation[4]] & (1 << 24)))
			return;

		// 보드 세팅
		for (int i = 0; i < 5; i++)
			tower[i] = board[order[i]][rotation[i]];

		solveBFS();
		return;
	}

	for (int i = 0; i < 4; i++) {
		// 중복 순열
		rotation[depth] = i;
		solveRotation(depth + 1);
	}
}
// 1. 보드배치 순서 (순열) : 5! = 120
void solution(int depth) {
	// 보드 배치 완료
	if (depth == 5) {
		solveRotation(0);
		return;
	}

	// 순열
	for (int i = 0; i < 5; i++) {
		if (choosed[i]) continue;

		choosed[i] = true;
		order[depth] = i;
		solution(depth + 1);
		choosed[i] = false;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int num = 0;
	for (int i = 0; i < 5; i++) {
		for (int r = 0; r < BOARD_SIZE; r++) {
			for (int c = 0; c < BOARD_SIZE; c++) {
				cin >> num;
				if (num == 1)
					board[i][0] |= (1 << (r * BOARD_SIZE + c));
			}
		}
	}

	// 회전된 판 할당
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j < 4; j++) {
			for (int k = 0; k < BOARD_SIZE * BOARD_SIZE; k++) {
				if (!(board[i][j - 1] & (1 << k))) continue;

				int origin_r = k / BOARD_SIZE;
				int origin_c = k % BOARD_SIZE;
				// 90도 회전 좌표
				int rotate_r = origin_c;
				int rotate_c = BOARD_SIZE - 1 - origin_r;

				board[i][j] |= (1 << (rotate_r * BOARD_SIZE + rotate_c));
			}
		}
	}

	solution(0);
	if (answer == INF)
		cout << -1 << '\n';
	else
		cout << answer << '\n';
	return 0;
}