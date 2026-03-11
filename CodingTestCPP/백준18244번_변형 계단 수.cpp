// 백준 18244번 : 변형 계단 수(https://www.acmicpc.net/problem/18244)
// 조건
// 1. 길이가 N(1<=N<=100)인 변형 계단 수의 개수
//  1-1. 변형 계단 수 : 인접한 자릿수가 연속 3번 이상 증/감 불가
//                    *0으로 시작할 수 있다.
//
// 풀이
// 1. 완탐(2^100 : 증/감) 불가
// 2. dp[digit][number][state]
//  2-1. digit번째 자리에 number수가 state 상태로 들어오는 총 경우의 수
// 3. state
//  3-1. 0 : 첫 번째 자리
//  3-2. 1 : 1회 증가
//  3-2. 2 : 2회 증가
//  3-3. 3 : 1회 감소
//  3-4. 4 : 2회 감소 
#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MOD = 1000000007;

int n, dp[101][10][5];

int solution() {
	if (n == 1) return 10;

	// 첫번째 자리 할당 (0-based)
	for (int i = 0; i < 10; i++) dp[0][i][0] = 1;

	for (int digit = 1; digit < n; digit++) {
		for (int num = 0; num <= 9; num++) {
			if (num > 0) {
				// 1 증가
				dp[digit][num][1] = (dp[digit][num][1] + ((dp[digit - 1][num - 1][0] + ((dp[digit - 1][num - 1][3] + dp[digit - 1][num - 1][4]) % MOD)) % MOD)) % MOD;
				// 2 증가
				dp[digit][num][2] = (dp[digit][num][2] + dp[digit - 1][num - 1][1]) % MOD;
			}
			if (num < 9) {
				// 1 감소
				dp[digit][num][3] = (dp[digit][num][3] + ((dp[digit - 1][num + 1][0] + ((dp[digit - 1][num + 1][1] + dp[digit - 1][num + 1][2]) % MOD)) % MOD)) % MOD;
				// 2 감소
				dp[digit][num][4] = (dp[digit][num][4] + dp[digit - 1][num + 1][3]) % MOD;
			}
		}
	}

	int answer = 0;
	for (int num = 0; num <= 9; num++)
		for (int state = 1; state < 5; state++)
			answer = (answer + dp[n - 1][num][state]) % MOD;

	return answer;
}

int main() {
	cin >> n;
	cout << solution() << '\n';
	return 0;
}