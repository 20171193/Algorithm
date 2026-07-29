// 프로그래머스(L3) : 카드 짝 맞추기
// 문제
// 1. 4x4 격자에 카드가 놓여있고, 커서로 카드를 뒤집어 같은 그림끼리 짝을 맞추는 게임.
//    board[i][j] : 0(이미 제거된 빈 칸) 또는 카드 그림 번호(같은 번호가 정확히 2장씩 존재)
// 2. 커서 조작
//    - 방향키 : 커서를 상하좌우로 1칸 이동
//    - Ctrl+방향키 : 해당 방향으로 "가장 가까운 카드가 있는 칸"까지 이동
//      (그 방향에 카드가 하나도 없으면 격자 끝 칸까지 이동)
//    - Enter : 커서 위치의 카드를 뒤집음(선택)
// 3. 카드 제거 규칙
//    - 카드 1장을 선택하면 앞면이 보임(뒤집힘)
//    - 카드 2장째를 선택했을 때
//      - 그림이 같으면 두 카드 모두 제거
//      - 그림이 다르면 두 카드 모두 다시 뒷면으로(선택 취소)
// 4. 커서 초기 위치 (r, c)에서 시작해서, 모든 카드를 제거하는 데 필요한
//    "최소 키 입력 횟수"(이동 + Enter)를 반환
// 조건
// 1. board : 4 x 4 크기의 2차원 배열
// 2. board의 각 원소는 0 또는 카드 그림 번호이며, 0이 아닌 번호는 정확히 2개씩 존재
// 3. r, c : 커서 초기 위치 (0 ≤ r, c ≤ 3)
// 풀이
// 1. 각 카드 좌표 매핑, 좌표-인덱스 매핑
// 2. 순열 : 최대 6! 

// 수정 : 다른 카드 만나더라도 엔터 입력 없으면 카드 안바뀜. 
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};

vector<vector<int>> bfs(pair<int,int> start, vector<vector<int>>& board){
	int n = board.size();
	vector<vector<int>> visited(n, vector<int>(n, 0));

	visited[start.first][start.second] = 1;
	queue<pair<int,int>> q;
	q.push(start);

	while(!q.empty()){
		auto cur = q.front();
		q.pop();

		for(int d = 0; d < 4; d++){
			int ny = cur.first + dy[d];
			int nx = cur.second + dx[d];
			if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
			if(visited[ny][nx] == 0 
				|| visited[ny][nx] > visited[cur.first][cur.second] + 1) {
				visited[ny][nx] = visited[cur.first][cur.second] + 1;
				q.push({ny,nx});
			}

			// ctrl + 방향키
			int cny = ny;
			int cnx = nx;
			bool canCtrl = false;
			while(true){
				// 벽까지 이동한 경우
				if(cnx < 0 || cny < 0 || cnx >= n || cny >= n) {
					cny -= dy[d];
        			cnx -= dx[d];
        			canCtrl = true;   
        			break;
				}
				// 카드를 만난 경우
				if(board[cny][cnx] != 0) {
					canCtrl = true;
					break;
				}

				cny += dy[d];
				cnx += dx[d];
			}

			if(canCtrl 
				&& (visited[cny][cnx] == 0 || visited[cny][cnx] > visited[cur.first][cur.second] + 1)) {
				visited[cny][cnx] = visited[cur.first][cur.second] + 1;
				q.push({cny, cnx});
			}
		}
	}

	return visited;
}

int GetDist(pair<int,int>& c, pair<int,int> p1, pair<int,int> p2, vector<vector<int>>& board) {
	pair<int,int> start, end;

	// 시작 지점 정하기 (cur-p1 / cur-p2)
	auto visited = bfs(c, board);
	if(visited[p1.first][p1.second] < visited[p2.first][p2.second])
		start = p1, end = p2;
	else
		start = p2, end = p1;
	// cur ~ start
	int dist = visited[start.first][start.second] - 1;	// 방문체크는 1부터
	

	// start ~ end
	visited = bfs(start, board);
	dist += visited[end.first][end.second] - 1;	// 방문체크는 1부터

	// 현재 위치 갱신 
	c = end;

	return dist;
}


int solution(vector<vector<int>> board, int r, int c) {
    int answer = 1e9;

	vector<vector<pair<int,int>>> cardPos;
	vector<int> cardIndex(7, -1);

	for(int i =0; i< board.size(); i++){
		for(int j = 0; j<board[i].size(); j++){
			if(board[i][j] != 0){
				if(cardIndex[board[i][j]] == -1){
					cardIndex[board[i][j]] = cardPos.size();
					cardPos.push_back({{i,j}});
				}
				else
					cardPos[cardIndex[board[i][j]]].push_back({i,j});
			}
		}
	}

	// 카드 순열
	do{
		int total = 0;
		pair<int, int> curPos = {r,c};
		vector<vector<int>> tempBoard = board;

		for(auto card : cardPos) {
			// 이동 키 + enter키(2)
			total += GetDist(curPos, card[0], card[1], tempBoard) + 2;
			tempBoard[card[0].first][card[0].second] = 0;
			tempBoard[card[1].first][card[1].second] = 0;
		}
		
		answer = min(answer, total);
	}while(next_permutation(cardPos.begin(), cardPos.end()));

    return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	struct TestCase { vector<vector<int>> board; int r, c, expected; };

	vector<TestCase> testCases = {
		{ {{1,0,0,3},{2,0,0,0},{0,0,0,2},{3,0,1,0}}, 1, 0, 14 }, // 공식 예제 1
		{ {{3,0,0,2},{0,0,1,0},{0,1,0,0},{2,0,0,3}}, 0, 1, 16 }, // 공식 예제 2
	};

	for (auto& tc : testCases) {
		int result = solution(tc.board, tc.r, tc.c);
		cout << "r=" << tc.r << " c=" << tc.c
			 << " | expected: " << tc.expected
			 << " | result: " << result
			 << " | " << (result == tc.expected ? "PASS" : "FAIL") << "\n";
	}

	return 0;
}