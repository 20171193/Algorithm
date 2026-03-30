// 백준 17780번 : 새로운 게임 (https://www.acmicpc.net/problem/17780)
// 조건
// 1. 턴
//  1-1. 1번부터 k번말까지 이동
//  1-2. 가장 아래있는 말만 이동 가능.
// 2. 말
//  2-1. 흰색 : 이동 후 위로 쌓음.
//  2-2. 빨간색 : 이동 후 이동하는 말들의 순서를 역순으로 변경
//  2-3. 파란색 : 이동 방향을 반대로 바꾼 후 이동(이동하려는 칸이 파란색일 경우 방향만 바꿈)
//  2-4. 범위 밖 : 파란색과 동일하게 방향만 전환
// 3. 종료조건
//  3-1. 말이 4개 쌓인 경우 (출력 : 턴 번호)
//  3-2. 계속 진행해도 끝나지 않는 경우 (출력 : -1)
//
// 풀이
// 1. 시뮬레이션 구현

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum COLOR { WHITE = 0, RED, BLUE };

int n, k, arr[12][12];

// 방향 우/좌/상/하
int dc[5] = { 0, 1,-1,0,0 };
int dr[5] = { 0, 0,0,-1,1 };

struct Piece {
	int index, direction, order;
	Piece(int i, int d, int o) : index(i), direction(d), order(o) {}
};

vector<Piece> pieceByTurn;
vector<vector<int>> piecesByMap;

int GetOpposite(int direction) {
	if (direction == 1) return 2;
	else if (direction == 2) return 1;
	else if (direction == 3) return 4;
	else return 3;
}

int solution() {
	int turn = 0;

	bool endFlag = false;
	while (!endFlag) {
		turn++;
		for (auto& p : pieceByTurn) {
			if (p.order != 0) continue;
			int nr = p.index / n + dr[p.direction];
			int nc = p.index % n + dc[p.direction];

			// 막혔거나 || 파란칸인 경우
			if ((nr < 0 || nr >= n || nc < 0 || nc >= n) || arr[nr][nc] == BLUE) {
				// 방향 전환 후 한 칸 이동
				p.direction = GetOpposite(p.direction);
				nr = p.index / n + dr[p.direction];
				nc = p.index % n + dc[p.direction];
				// 반대 방향도 같은 조건인 경우 continue
				if ((nr < 0 || nr >= n || nc < 0 || nc >= n) || arr[nr][nc] == BLUE)
					continue;
			}

			vector<int> temp = piecesByMap[p.index];

			// 현재 칸 비우기
			piecesByMap[p.index].clear();

			// 빨간칸인 경우 뒤집기
			if (arr[nr][nc] == RED)
				reverse(temp.begin(), temp.end());

			int nIndex = nr * n + nc;
			int orderIndex = piecesByMap[nIndex].size();
			for (int i : temp) {
				pieceByTurn[i].index = nIndex;
				pieceByTurn[i].order = orderIndex++;
			}

			// 다음 칸 뒤에 쌓기
			piecesByMap[nIndex].insert(piecesByMap[nIndex].end(), temp.begin(), temp.end());
			if (piecesByMap[nIndex].size() >= 4) {
				endFlag = true;
				break;
			}
		}

		if (turn >= 1000)
			break;
	}

	if (turn >= 1000)
		return -1;

	return turn;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];

	piecesByMap.assign(n * n, {});
	for (int i = 0; i < k; i++) {
		int r, c, d;
		cin >> r >> c >> d;

		// 0-based index
		int index = (r - 1) * n + (c - 1);
		pieceByTurn.push_back(Piece(index, d, 0));
		piecesByMap[index].push_back(i);
	}

	std::cout << solution() << '\n';
	return 0;
}