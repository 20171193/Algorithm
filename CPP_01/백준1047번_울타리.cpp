// 백준 1047번 : 울타리 (https://www.acmicpc.net/problem/1047)
// 조건
// 1. 정원을 구성하는 나무 (1<=x,y,t<=1,000,000)
// 2. 나무를 모두 감싸는(접해도 됨) 울타리를 만들어야 할 때, 벌목해야하는 나무의 최소 개수
//
// 풀이
// 1. 가능한 경계 설정
// 2. 벌목
//  2-1.      무조건 벌목 : 경계 밖
//  2-2. 부족한 경우 벌목 : 경계 안(큰 나무부터)
// 
// 시도 
// 1. O(N^4)에서 매번 배열할당(내부에 위치한 나무)
//  - 수정 : 그냥 N번 재순회 (외부(O(N)) -> 내부(O(N), 조기 탈출)
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_TREE_COUNT = 41;

struct Tree {
	int y, x, height;
	bool operator>(const Tree& other) const {
		return height > other.height;
	}
};

int n, answer = MAX_TREE_COUNT;
Tree trees[MAX_TREE_COUNT];

int logging(int lx, int rx, int ty, int by) {
	int targetSize = (rx - lx) * 2 + (by - ty) * 2;
	int logCount = 0, curSize = 0;

	// 경계 외부 처리
	for (int i = 0; i < n; i++) {
		// 외부:무조건 벌목
		if (trees[i].y < ty || trees[i].y > by || trees[i].x < lx || trees[i].x > rx) {
			curSize += trees[i].height;
			logCount++;
		}

		if (logCount >= answer) return MAX_TREE_COUNT;
	}

	// 수정 : 메모리 할당 없이 재순회
	// 경계 내부 처리 (높이 기준 내림차 정렬된 배열)
	for (int i = 0; i < n; i++) {
		// 조건 충족 시 바로 break;
		if (curSize >= targetSize) break;

		if (trees[i].y >= ty && trees[i].y <= by && trees[i].x >= lx && trees[i].x <= rx) {
			curSize += trees[i].height;
			logCount++;
		}

		if (logCount >= answer) return MAX_TREE_COUNT;
	}

	return logCount;
}

void solution() {
	// 경계면 설정 (오름차 정렬, 중복 제거)
	vector<int> posY(n), posX(n);
	for (int i = 0; i < n; i++) {
		posY[i] = trees[i].y;
		posX[i] = trees[i].x;
	}

	sort(posX.begin(), posX.end());
	posX.erase(unique(posX.begin(), posX.end()), posX.end());

	sort(posY.begin(), posY.end());
	posY.erase(unique(posY.begin(), posY.end()), posY.end());

	// 나무 높이 기준 내림차 정렬
	sort(trees, trees + n, greater<Tree>());

	// x 경계
	for (int lxi = 0; lxi < posX.size(); lxi++) {
		for (int rxi = lxi; rxi < posX.size(); rxi++) {
			// y 경계
			for (int tyi = 0; tyi < posY.size(); tyi++) {
				for (int byi = tyi; byi < posY.size(); byi++) {
					answer = min(answer, logging(posX[lxi], posX[rxi], posY[tyi], posY[byi]));
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> trees[i].y >> trees[i].x >> trees[i].height;

	solution();

	cout << answer << '\n';
	return 0;
}