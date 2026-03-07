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
#include <algorithm>
using namespace std;

struct Piece {
	int h, w, cnt;
	int row[10] = {};
};

int l;
Piece pieces[5];

// r,c 칸에 조각 삽입 가능여부
bool placeable(int r, int c, int pi, const int* placed) {
	for (int cr = 0; cr < pieces[pi].h; cr++) {
		if (placed[r + cr] & (pieces[pi].row[cr] << c))
			return false;
	}
	return true;
}

// 가장 가까운 빈칸 찾기
bool findEmpty(const int* placed, int& sr, int& sc) {
	for (int r = 0; r < l; r++) {
		for (int c = 0; c < l; c++) {
			if ((placed[r] & (1 << c)) == 0) {
				sr = r;
				sc = c;
				return true;
			}
		}
	}
	return false;
}

// 조각 인덱스 할당
void place(int r, int c, int pi, string& answer) {
	for (int cr = 0; cr < pieces[pi].h; cr++) {
		int rowBit = (pieces[pi].row[cr] << c);

		for (int cc = 0; cc < l; cc++) {
			if (rowBit & (1 << cc))
				answer[cc + (r + cr) * (l + 1)] = pi + '1'; // 인덱스 0-based
		}
	}
}

bool dfs(int used, int placed[10], string& answer) {
	int sr, sc;
	if (!findEmpty(placed, sr, sc)) return true;

	for (int i = 0; i < 5; i++) {
		if (used & (1 << i)) continue;

		for (int pr = 0; pr < pieces[i].h; pr++) {
			for (int pc = 0; pc < pieces[i].w; pc++) {
				if ((pieces[i].row[pr] & (1 << pc)) == 0) continue;

				int r = sr - pr;
				int c = sc - pc;

				if (r < 0 || r + pieces[i].h > l || c < 0 || c + pieces[i].w > l) continue;
				if (!placeable(r, c, i, placed)) continue;

				// 조각 삽입
				for (int cr = 0; cr < pieces[i].h; cr++) placed[r + cr] |= (pieces[i].row[cr] << c);

				if (dfs(used | (1 << i), placed, answer)) {
					place(r, c, i, answer);
					return true;
				}

				// 원복
				for (int cr = 0; cr < pieces[i].h; cr++) placed[r + cr] ^= (pieces[i].row[cr] << c);
			}
		}
	}

	return false;
}

string solution() {
	// 출력 버퍼
	string answer(l * (l + 1), '0');
	for (int r = 0; r < l; r++) answer[r * (l + 1) + l] = '\n';

	int placed[10] = {};
	if (!dfs(0, placed, answer))
		return "gg\n";

	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> l;

	int totalCnt = 0;
	for (int i = 0; i < 5; i++) {
		cin >> pieces[i].h >> pieces[i].w;

		string temp;
		for (int r = 0; r < pieces[i].h; r++) {
			cin >> temp;
			for (int c = 0; c < pieces[i].w; c++) {
				if (temp[c] == '#') {
					pieces[i].row[r] |= (1 << c);
					pieces[i].cnt++;
					totalCnt++;
				}
			}
		}
	}

	if (totalCnt != l * l) {
		cout << "gg" << '\n';
		return 0;
	}

	cout << solution();
	return 0;
}