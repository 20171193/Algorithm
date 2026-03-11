// 백준 17406번 : 배열 돌리기 4
// 조건
// 1. 주어진 회전 연산으로 나올 수 있는 배열의 최솟값
// 2. 배열의 값 : 열마다 행의 합+
// 풀이
// 1. 회전 연산 구현
// 2. 순열 (최대 6!)
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

constexpr int INF_ROW_SUM = 5001;

int n, m, k, ret = INF_ROW_SUM;
vector<vector<int>> matrix;
tuple<int, int, int> opers[7];

// 시계/반시계 회전
void Rotate(int operIdx, bool isCCW) {
	int r = get<0>(opers[operIdx]) - 1;	// 입력은 1-based, 실제 할당은 0-based
	int c = get<1>(opers[operIdx]) - 1;
	int s = get<2>(opers[operIdx]);
	for (int layer = 1; layer <= s; layer++) {
		int top = r - layer, bottom = r + layer;
		int left = c - layer, right = c + layer;

		if (isCCW) {
			int temp = matrix[top][left];
			for (int j = left; j < right; j++)matrix[top][j] = matrix[top][j + 1];
			for (int i = top; i < bottom; i++)matrix[i][right] = matrix[i + 1][right];
			for (int j = right; j > left; j--)matrix[bottom][j] = matrix[bottom][j - 1];
			for (int i = bottom; i > top + 1; i--)matrix[i][left] = matrix[i - 1][left];
			matrix[top + 1][left] = temp;
		}
		else {
			int temp = matrix[top][left];
			for (int i = top; i < bottom; i++) matrix[i][left] = matrix[i + 1][left];
			for (int j = left; j < right; j++) matrix[bottom][j] = matrix[bottom][j + 1];
			for (int i = bottom; i > top; i--) matrix[i][right] = matrix[i - 1][right];
			for (int j = right; j > left + 1; j--) matrix[top][j] = matrix[top][j - 1];
			matrix[top][left + 1] = temp;
		}
	}
}

void dfs(int mask) {
	if (mask == (1 << k) - 1) {
		for (int i = 0; i < n; i++)
			ret = min(ret, accumulate(matrix[i].begin(), matrix[i].end(), 0));
		return;
	}

	for (int i = 0; i < k; i++) {
		if (mask & (1 << i)) continue;

		// 회전(시계 방향)
		Rotate(i, false);
		dfs(mask | (1 << i));
		// 원복(반시계 방향)
		Rotate(i, true);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;

	matrix.assign(n, vector<int>(m));
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			cin >> matrix[r][c];

	for (int i = 0; i < k; i++) {
		int r, c, s;
		cin >> r >> c >> s;
		opers[i] = make_tuple(r, c, s);
	}

	dfs(0);

	cout << ret << '\n';
	return 0;
}
