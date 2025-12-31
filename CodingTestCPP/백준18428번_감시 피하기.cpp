// 백준 18428번 : 감시 피하기(https://www.acmicpc.net/problem/18428)
// 조건
// 1. 선생님(T)는 상,하,좌,우로 장애물 이전의 모든 칸 확인 가능.
//  1-1. 선생님은 다수
// 2. 맵에 장애물을 3개 설치해 감시를 피할 수 있는지 출력
// 3. 맵(N*N, 3<=N<=6)
// 풀이
// 1. 장애물 설치 조합 36c3  
//  -> 3중 for문
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n;
char arr[6][6];

bool OnDetact(int tPos, const vector<char>& _arr) {
	int cursor;
	// 상 탐색
	cursor = tPos - n;
	while (cursor >= 0) {
		if (_arr[cursor] == 'S') return true;
		if (_arr[cursor] == 'O') break;
		cursor -= n;
	}
	// 하 탐색
	cursor = tPos + n;
	while (cursor < n * n) {
		if (_arr[cursor] == 'S') return true;
		if (_arr[cursor] == 'O') break;
		cursor += n;
	}

	int bound = tPos % n;
	// 좌 탐색
	for (int dist = 1; dist <= bound; dist++) {
		cursor = tPos - dist;
		if (_arr[cursor] == 'S') return true;
		if (_arr[cursor] == 'O') break;
	}
	// 우 탐색
	for (int dist = 1; dist <= n - bound - 1; dist++) {
		cursor = tPos + dist;
		if (_arr[cursor] == 'S') return true;
		if (_arr[cursor] == 'O') break;
	}

	return false;
}

bool solution() {
	int maxIndex = n * n;
	// 1차원 포맷
	vector<char> _arr(maxIndex);
	// 선생님 인덱스
	vector<int> tPoses;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int idx = i * n + j;
			_arr[idx] = arr[i][j];
			if (_arr[idx] == 'T')
				tPoses.push_back(idx);
		}
	}

	for (int i = 0; i < maxIndex - 2; i++) {
		if (_arr[i] != 'X') continue;
		for (int j = i + 1; j < maxIndex - 1; j++) {
			if (_arr[j] != 'X') continue;
			for (int k = j + 1; k < maxIndex; k++) {
				if (_arr[k] != 'X') continue;

				// 장애물 설치
				_arr[i] = _arr[j] = _arr[k] = 'O';

				bool successFlag = true;
				for (int tIdx : tPoses) {
					if (OnDetact(tIdx, _arr)) {
						successFlag = false;
						break;
					}
				}

				if (successFlag)
					return true;

				// 원복 
				_arr[i] = _arr[j] = _arr[k] = 'X';
			}
		}
	}

	return false;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];

	if (solution())
		cout << "YES" << '\n';
	else
		cout << "NO" << '\n';
	return 0;
}