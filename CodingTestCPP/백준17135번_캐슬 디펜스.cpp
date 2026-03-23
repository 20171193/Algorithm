// 백준 17135번 : 캐슬 디펜스
// 조건
// 1. 보드의 각 칸마다 최대 하나의 적이 포함
// 2. N+1번 행의 모든 칸에는 '성'이 있음.
//  2-1. 총 3명의 궁수를 성에 배치. (칸마다 최대 1명)
// 3. 궁수
//  3-1. 턴마다 궁수는 적 하나를 공격(모두 동시에)
//  3-2. D거리 이내의 가장 가까운 적을 우선 공격(D거리이내 가장 왼쪽에 위치한 적)
//       *거리는 맨해튼 거리 사용
//  3-3. 동일한 적을 궁수 여러명이 공격할 수 있음
// 4. 적
//  4-1. 적은 아래로 한 칸 이동(R+1)
//  4-2. 성이 있는 칸으로 이동한 경우 게임에서 제외
//  4-3. 모든 적이 격자판에서 제외되면 게임 종료
// 5. 궁수의 공격으로 제거한 적의 최대 수 출력
// 6. 격자 N*M(3<=N,M<=15), 사정거리(1<=D<=10)
// 풀이
// 1. 궁수를 어떤 열에 배치할지(조합)
// 2. 조합 + 시뮬레이션 (15c3 * 15)
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
using namespace std;

int n, m, d, enemyCnt, ret = -1;
vector<int> board;
unordered_set<int> masked;

bool hasEnemy(const vector<int>& b) {
	for (int mask : b) {
		if (mask > 0) return true;
	}
	return false;
}

int simulation(int mask) {
	// 원본 보드 복사
	vector<int> curBoard = board;
	int killCnt = 0;

	for (int step = 0; step < n; step++) {
		// 1. 적 탐지 
		vector<pair<int, int>> targets;
		for (int acherC = 0; acherC < m; acherC++) {
			if (!(mask & (1 << acherC))) continue;
			for (int curDist = 1; curDist <= d; curDist++) {
				bool findFlag = false;
				for (int c = acherC - (curDist - 1); c <= acherC + (curDist - 1); c++) {
					if (c < 0 || c >= m) continue;
					int r = n - (curDist - abs(c - acherC));	// 맨해튼
					if (r < 0 || r >= n) continue;

					if (curBoard[r] & (1 << c)) {
						targets.push_back({ r,c });	// 중복 허용하여 타겟 할당
						findFlag = true;
						break;
					}
				}

				if (findFlag) break;
			}
		}

		// 2. 적 제거, 보드 적용
		for (auto& p : targets) {
			if (curBoard[p.first] & (1 << p.second)) {
				curBoard[p.first] &= ~(1 << p.second);
				killCnt++;
			}
		}

		// 3. 적 이동
		for (int r = n - 1; r > 0; r--) {
			curBoard[r] = curBoard[r - 1];
		}
		curBoard[0] = 0;	// 이동 범위 줄이기 

		if (!hasEnemy(curBoard))
			break;
	}

	return killCnt;
}

void solution(int mask, int cnt) {
	if (cnt == 3) {
		if (masked.find(mask) == masked.end()) {
			ret = max(ret, simulation(mask));
			masked.insert(mask);
		}
		return;
	}

	for (int i = 0; i < m; i++) {
		if (mask & (1 << i)) continue;
		solution(mask | (1 << i), cnt + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m >> d;

	board.assign(n, 0);
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			int bi;
			cin >> bi;
			if (bi) {
				board[r] |= (1 << c);
				enemyCnt++;
			}
		}
	}

	solution(0, 0);

	cout << ret << '\n';
	return 0;
}