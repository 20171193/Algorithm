// 백준 3109번 : 빵집(https://www.acmicpc.net/problem/3109)
// 조건
// 1. r*c, (r<=10,000) (c<=500)
// 2. 우상,우,우하만 연결 가능
//
// 풀이
// 1. 매 열에서 다음 열의 행 가중치 부여
//  1-1. 오름차 진행 시 자신보다 -1낮은 행부터 우선 탐색
//       즉, r-1 > r > r+1 순으로
// 2. 연결 여부 확인(DFS) + 방향 우선순위(그리디)
// 
// 수정
// 1. 불필요한 연산 줄이기
//  1-1. 오름차/내림차 두 번 진행 -> 오름차 한 번 진행
// 2. 백트래킹 방문처리
//  2-1. 방문 실패 시 원복 할 필요없음. (어차피 실패한 노드)
#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

int r, c;
bool visited[10001][501];
string board[10001];

int asc[3] = { -1,0,1 };

bool dfs(int cr, int cc) {
	if (cc >= c) return true;

	for (int i = 0; i < 3; i++) {
		int nr = cr + asc[i];
		int nc = cc + 1;
		if (nr < 0 || nr >= r) continue;
		if (board[nr][nc] == 'x') continue;
		if (visited[nr][nc]) continue;

		visited[nr][nc] = true;
		if (dfs(nr, nc)) return true;
	}

	return false;
}

int solution() {
	int answer = 0;

	for (int cr = 0; cr < r; cr++) {
		if (dfs(cr, 0)) answer++;
	}

	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> r >> c;
	for (int i = 0; i < r; i++)
		cin >> board[i];

	cout << solution() << '\n';
	return 0;
}
