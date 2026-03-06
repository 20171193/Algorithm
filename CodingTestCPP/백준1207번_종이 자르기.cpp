// 백준 1207번 : 종이 자르기
// 조건
// 1. 나눠진 다섯 조각을 배치 해 L*L 정사각형으로 복구
//
// 풀이
// 1. 백트래킹 완탐
//  1-1. dfs : 놓을 수 있는 지 확인
//  1-2. 백트래킹 : 실제 인덱스 할당
// 2. 조각별 비트마스킹
//  2-1. 전체 보드에서 해당 조각이 위치할 수 있는 모든 경우 비트마스킹 할당
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int l, h[5], w[5], pieces[5][11], selected[5];

struct Placement {
	int row[11] = {};
};

// 각 조각별 배치도
vector<Placement> placements[5];

bool placeable(const int* pieceRow, const int* board) {
	for (int r = 0; r < l; r++) {
		if (board[r] & pieceRow[r])
			return false;
	}
	return true;
}

bool solution(int used, int placed[11]) {
	if (used == (1 << 5) - 1) return true;


	for (int i = 0; i < 5; i++) {
		if (used & (1 << i)) continue;

		for (int j = 0; j < placements[i].size(); j++) {
			if (!placeable(placements[i][j].row, placed)) continue;	// 비트 중복 확인

			// 방문 체크
			for (int r = 0; r < l; r++) placed[r] |= placements[i][j].row[r];

			// 조각별 배치도 인덱스 할당
			selected[i] = j;
			if (solution(used | (1 << i), placed))  return true;

			// 원복
			for (int r = 0; r < l; r++) placed[r] ^= placements[i][j].row[r];
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> l;

	string temp;
	int cnt = 0;
	for (int i = 0; i < 5; i++) {
		cin >> h[i] >> w[i];
		for (int y = 0; y < h[i]; y++) {
			cin >> temp;
			for (int x = 0; x < w[i]; x++) {
				if (temp[x] == '#') {
					pieces[i][y] |= (1 << x);	// 원본 조각 할당
					cnt++;
				}
			}
		}
	}

	// 조각 개수와 보드 크기가 맞지 않은 경우
	if (cnt != l * l) {
		cout << "gg" << '\n';
		return 0;
	}

	// 조각별 배치도 할당(보드내 모든 위치)
	for (int i = 0; i < 5; i++) {
		for (int dy = 0; dy <= l - h[i]; dy++) {
			for (int dx = 0; dx <= l - w[i]; dx++) {
				Placement p;
				for (int r = 0; r < h[i]; r++)
					p.row[dy + r] = (pieces[i][r] << dx);
				placements[i].push_back(p);
			}
		}
	}

	int placed[11] = {};
	if (solution(0, placed)) {
		// 출력 버퍼 생성
		string answer(l * (l + 1), '\n');
		for (int i = 0; i < 5; i++) {
			const auto& p = placements[i][selected[i]];
			for (int r = 0; r < l; r++)
				for (int c = 0; c < l; c++)
					if (p.row[r] & (1 << c))
						answer[r * (l + 1) + c] = i + '1';
		}
		cout << answer;
	}
	else
		cout << "gg" << '\n';
	return 0;
}