// 백준 1035번 : 조각 움직이기
// 조건
// 1. 최대 5개의 조각을 상/하/좌/우로 움직여서
//    모든 조각이 연결 요소를 이룬다고 했을 때, 
//    조각을 움직이는 최소 횟수 
// 
// 풀이
// 1. 가능한 연결요소 모두 만들기(bfs)
//   : 영역 전개((4*2)^5) - 약 3만
// 2. 연결요소의 각 좌표에 조각 매칭(순열)
//   : 5! 
// 
// 실패
// - 이유 : 0번쨰 조각의 좌표를 기준으로 영역을 전개함.
//          그리디 전제 자체가 틀림
//        => 0번째 조각을 움직여야만하는 경우가 있음.
// - 수정 : 25개의 좌표에서 가능한 모든 연결요소 생성
//          연결요소 개수 최대 25c5로 충분히 가능
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };

constexpr int INF = 126;
int ret = INF;
bool masked[1 << 25];
string board[5];

vector<pair<int, int>> pieces;

struct Node {
	int y, x, mask, cnt;
};

int Manhattan(const pair<int, int>& a, const pair<int, int>& b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

void dfs(int y, int x, int mask, int cnt, vector<int>& masks) {
	if (cnt == pieces.size()) {
		if (!masked[mask]) {
			masked[mask] = true;
			masks.push_back(mask);
		}
		return;
	}


	for (int d = 0; d < 4; d++) {
		int ny = dy[d] + y;
		int nx = dx[d] + x;
		if (ny < 0 || ny >= 5 || nx < 0 || nx >= 5) continue;
		int nBit = 1 << (ny * 5 + nx);
		if (mask & nBit) continue;

		// 전개 형식으로 진행
		dfs(ny, nx, mask | nBit, cnt + 1, masks);
		dfs(y, x, mask | nBit, cnt + 1, masks);
	}
}

int solution() {
	// *** 오답 코드 *** 
	// 0번째 조각 기준
	// 가능한 연결요소 모두 마스킹
	//queue<Node> q;
	//auto p = pieces[0];
	//int curMask = 1 << (5 * p.first + p.second);
	//q.push({ p.first, p.second, curMask, 1 });
	//masked[curMask] = true;

	//vector<int> masks;
	//while (!q.empty()) {
	//	auto cur = q.front(); q.pop();

	//	for (int d = 0; d < 4; d++) {
	//		int ny = dy[d] + cur.y;
	//		int nx = dx[d] + cur.x;
	//		if (ny < 0 || ny >= 5 || nx < 0 || nx >= 5) continue;
	//		int nMask = cur.mask | (1 << (ny * 5 + nx));
	//		if (masked[nMask]) continue;

	//		masked[nMask] = true;

	//		if (cur.cnt + 1 == pieces.size()) {
	//			masks.push_back(nMask);
	//			continue;
	//		}
	//		
	//		// 영역 전개
	//		q.push({ ny,nx,nMask, cur.cnt + 1 });
	//		q.push({ cur.y, cur.x, nMask, cur.cnt + 1 });
	//	}
	//}
	
	// 보드 내 가능한 모든 연결요소
	vector<int> masks;
	for (int r = 0; r < 5; r++) 
		for (int c = 0; c < 5; c++) 
			dfs(r, c, 1 << (r * 5 + c), 1, masks);

	// 영역의 좌표마다 가장 가까운 조각 매칭
	int answer = INF;
	for (int mask : masks) {
		// 다시 좌표로 변환
		vector<pair<int, int>> targetPos;
		for (int i = 0; i < 25; i++) {
			if (mask & (1 << i))
				targetPos.push_back({ i / 5, i % 5 });
		}

		// 각 좌표에 조각매칭 (5!)
		vector<int> perm(pieces.size());
		iota(perm.begin(), perm.end(), 0);
		
		do {
			int totalDist = 0;
			for (int i = 0; i < pieces.size(); i++) 
				totalDist += Manhattan(pieces[perm[i]], targetPos[i]);
			answer = min(answer, totalDist);
		} while (next_permutation(perm.begin(), perm.end()));
	}

	return answer;
}

int main() {
	for (int r = 0; r < 5; r++) {
		cin >> board[r];
		for (int c = 0; c < 5; c++) {
			if (board[r][c] == '*') 
				pieces.push_back({ r,c });
		}
	}

	cout << solution() << '\n';
	return 0;
}


