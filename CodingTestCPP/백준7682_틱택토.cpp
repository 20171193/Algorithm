// 백준 7682번 : 틱택토(https://www.acmicpc.net/problem/7682)
// 조건
// 1. 틱택토 게임 : 가로/세로/대각선으로 3칸을 잇는 데 성공하면 종료
//  1-1. 판의 상태가 주어졌을 때, 발생할 수 있는 최종 상태인지 판별
//
// 풀이
// 1. 턴 종료 확인(valid)
//  1-1. 홀수 턴 (x가 이겼거나, 승부가 나지 않은 상태)
//  1-2. 짝수 턴 (o가 이긴상태)
// 2. 나머지 모든 상태(invalid)
// 3. 종료조건 미리 마스킹 후 비트마스킹
#include <iostream>
#include <vector>
#include <string>
using namespace std;

constexpr int BOARD_WIDTH = 3, BOARD_SIZE = 9;
const string valid = "valid", invalid = "invalid";
vector<string> input, answer;
void solution() {
	answer.assign(input.size(), "");

	// 종료조건 비트 할당 (총 8개)
	// 행(3) + 열(3) + 대각(2)
	vector<int> endbits;
	int width = 3, bit = 0;
	// 행 할당
	for (int i = 0; i < BOARD_SIZE; i += BOARD_WIDTH) {
		bit = 0;
		for (int j = 0; j < BOARD_WIDTH; j++)
			bit |= (1 << (i + j));
		endbits.push_back(bit);
	}
	// 열 할당
	for (int i = 0; i < BOARD_WIDTH; i++) {
		bit = 0;
		for (int j = 0; j < BOARD_SIZE; j += BOARD_WIDTH)
			bit |= (1 << (i + j));
		endbits.push_back(bit);
	}
	// 대각 할당 
	bit = 0;
	for (int i = 0; i < BOARD_SIZE; i += (BOARD_WIDTH + 1)) bit |= (1 << i);
	endbits.push_back(bit);
	bit = 0;
	for (int i = BOARD_WIDTH - 1; i <= BOARD_SIZE - BOARD_WIDTH; i += (BOARD_WIDTH - 1)) bit |= (1 << i);
	endbits.push_back(bit);

	for (int t = 0; t < input.size(); t++) {
		int xbit = 0, obit = 0, xCount = 0, oCount = 0;
		for (int i = 0; i < input[t].size(); i++) {
			if (input[t][i] == 'X') {
				xbit |= (1 << i);
				xCount++;
			}
			else if (input[t][i] == 'O') {
				obit |= (1 << i);
				oCount++;
			}
		}

		// 1. 턴 확인
		if ((xCount != oCount + 1) && (xCount != oCount)) {
			answer[t] = invalid;
			continue;
		}

		// 승리 여부 할당
		bool xWinFlag = false, oWinFlag = false;
		for (int i = 0; i < endbits.size(); i++) {
			int endbit = endbits[i];
			if ((endbit & xbit) == endbit) xWinFlag = true;
			if ((endbit & obit) == endbit) oWinFlag = true;
		}

		// 2. 승리 조건 확인
		if (xWinFlag && oWinFlag) {
			answer[t] = invalid;
			continue;
		}

		if (xWinFlag) {
			answer[t] = (xCount == oCount + 1) ? valid : invalid;
			continue;
		}
		if (oWinFlag) {
			answer[t] = (xCount == oCount) ? valid : invalid;
			continue;
		}

		// 3. 종료 조건 확인
		answer[t] = (xCount + oCount == BOARD_SIZE) ? valid : invalid;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	// input
	string temp;
	while (true) {
		cin >> temp;
		if (temp == "end") break;
		input.push_back(temp);
	}

	// solve
	solution();

	// output
	for (string& ans : answer)
		cout << ans << '\n';
	return 0;
}