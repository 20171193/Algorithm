// 백준 15989번 : 1,2,3 더하기 4(https://www.acmicpc.net/problem/15989)
// 조건
// 1. n(1<=10,000)을 1,2,3의 합으로 나타내는 모든 방법의 수 
// 
// 풀이
// 1. dp 점화식
//   dp[n][1] = 1
//   n>=2, dp[n][2] = dp[n-1][1] + dp[n-2][2]
//   n>=3, dp[n][3] = dp[n-1][1] + dp[n-2][2] + dp[n-3][3]
#include <iostream>
#include <algorithm>
using namespace std;

int n, t, maxN = 0, arr[10001], dp[10001][4];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> arr[i];
		maxN = max(maxN, arr[i]);
	}

	dp[0][1] = dp[0][2] = dp[0][3] = 1;
	for (int i = 1; i <= maxN; i++) {
		dp[i][1] = 1;
		dp[i][2] = dp[i][1] + (i - 2 >= 0 ? dp[i - 2][2] : 0);
		dp[i][3] = dp[i][2] + (i - 3 >= 0 ? dp[i - 3][3] : 0);
	}

	for (int i = 0; i < t; i++)
		cout << dp[arr[i]][3] << '\n';

	return 0;
}