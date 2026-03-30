// 백준 23288번 : 주사위 굴리기 2 (https://www.acmicpc.net/problem/23288)
// 
// 조건
// 1. 주사위 (위1,우3,좌4,뒤2,앞5,아래6)
// 2. 이동 (최초 이동 방향은 동쪽)
//  2-1. 이동 방향에 칸이 없으면 반대로 한 칸 이동
//  2-2. 이동한 칸의 점수를 획득
// 3. 방향 (주사위 아랫 면의 수 A, 칸의 수 B)
//  3-1. A > B : 시계 방향으로 회전
//  3-2. A < B : 반시계 방향으로 회전
//  3-3. A = B : 방향 유지
// 4. 점수 (칸의 수 * 칸의 수가 동일한 이어진 영역 개수)
// 5. 각 이동에서 획득하는 점수의 합 출력
//
// 풀이
// 1. BFS 영역 구분 (획득 가능한 점수 할당)
// 2. 주사위 회전 시뮬레이션
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

enum DiceFace { RIGHT = 0, FRONT, LEFT, BACK, TOP, BOTTOM };

int n, m, k, board[21][21], score[21][21], dice[6];

// 시계방향 할당(최초 동쪽, 동/남/서/북)
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

void bfs(int r, int c) {
	int num = board[r][c], cnt = 0;

	vector<pair<int, int>> path;
	queue<pair<int, int>> q;

	q.push({ r,c });
	path.push_back({ r,c });
	score[r][c] = 1;
	cnt++;

	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = cur.first + dy[d];
			int nx = cur.second + dx[d];
			if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
			if (board[ny][nx] != num || score[ny][nx]) continue;

			q.push({ ny,nx });
			path.push_back({ ny,nx });
			score[ny][nx] = 1;
			cnt++;
		}
	}

	for (auto& p : path)
		score[p.first][p.second] = cnt;
}

DiceFace GetOpposite(DiceFace face) {
	if (face == RIGHT) return LEFT;
	if (face == LEFT) return RIGHT;
	if (face == FRONT) return BACK;
	if (face == BACK) return FRONT;
	if (face == TOP) return BOTTOM;
	if (face == BOTTOM) return TOP;
}

void Rotate(int d) {
	// 1. 이동 전/후 앞/뒷 면은 유지
	// 2. 이동 방향에 위치한 면(A), 이동 방향에 반대에 위치한 면(B), 윗면(C), 아랫면(D)
	//  : A->D / B->C / C->A / D->B
	int opposite = GetOpposite(static_cast<DiceFace>(d));

	int originTemp = dice[d];
	dice[d] = dice[TOP];
	dice[TOP] = dice[opposite];
	dice[opposite] = dice[BOTTOM];
	dice[BOTTOM] = originTemp;
}

int solution() {
	// 영역 구분, 영역 크기 bfs
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			if (!score[r][c])
				bfs(r, c);

	// 주사위 초기화
	dice[TOP] = 1, dice[BACK] = 2, dice[RIGHT] = 3;
	dice[LEFT] = 4, dice[FRONT] = 5, dice[BOTTOM] = 6;

	int totalScore = 0, curDir = 0, curRow = 0, curCol = 0;

	while (k > 0) {
		int nextRow = curRow + dy[curDir];
		int nextCol = curCol + dx[curDir];
		if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= m) {
			curDir = (curDir + 2) % 4;	// 반대 방향 전환
			continue;
		}

		totalScore += score[nextRow][nextCol] * board[nextRow][nextCol];
		curRow = nextRow;
		curCol = nextCol;

		// 주사위 굴리기
		Rotate(curDir);

		// 다음 방향 할당
		if (dice[BOTTOM] > board[curRow][curCol])		// 시계 방향
			curDir = curDir + 1 > 3 ? 0 : curDir + 1;
		else if (dice[BOTTOM] < board[curRow][curCol])	// 반시계 방향
			curDir = curDir - 1 < 0 ? 3 : curDir - 1;

		k--;
	}

	return totalScore;
}

int main() {
	cin >> n >> m >> k;
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			cin >> board[r][c];

	cout << solution() << '\n';
	return 0;
}