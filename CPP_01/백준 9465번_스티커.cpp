// 백준 9465번 스티커

#include <iostream>
using namespace std;
// dp 풀이
// 맨 왼쪽 변부터 최적의 점수를 누적

// y기준
// dp[2][0] = dp[1][1] or dp[0][1]
// dp[2][1] = dp[1][0] or dp[0][0]

int t, n, a[100001][2], dp[100001][2];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 0; i < n * 2; i++)
		{
			cin >> a[i <= n - 1 ? i : i - n][i <= n - 1 ? 0 : 1];
		}

		dp[0][0] = a[0][0];
		dp[0][1] = a[0][1];
		dp[1][0] = dp[0][1] + a[1][0];
		dp[1][1] = dp[0][0] + a[1][1];

		for (int i = 2; i < n; i++)
		{
			dp[i][0] = max(max(dp[i - 2][1], dp[i - 1][1]) + a[i][0], dp[i - 1][0]);
			dp[i][1] = max(max(dp[i - 2][0], dp[i - 1][0]) + a[i][1], dp[i - 1][1]);
		}
		cout << max(dp[n - 1][1], dp[n - 1][0]) << '\n';
	}

	return 0;
}