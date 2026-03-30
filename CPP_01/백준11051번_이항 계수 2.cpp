// 백준 11051번 : 이항 계수 2(https://www.acmicpc.net/problem/11051()
// nCk
// n! / (n-k)! * k!
#include <iostream>
using namespace std;

constexpr int MOD = 10007;
int n, k, dp[1001][1001];

int main()
{
	cin >> n >> k;

	dp[0][0] = dp[1][0] = dp[1][1] = dp[2][0] = dp[2][2] = 1;
	dp[2][1] = 2;
	for (int i = 2; i <= n; i++)
	{
		dp[i][0] = dp[i][i] = 1;
		for (int j = 1; j < i; j++)
		{
			dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
		}
	}

	cout << dp[n][k] << '\n';
	return 0;
}