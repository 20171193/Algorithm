// 백준 17404번 : RGB거리 2
// 앞뒤로 인접한 집의 색과 다르게 칠해야함.
#include <iostream>
#include <vector>
using namespace std;

constexpr int INF = 1000001;

int n, costs[1001][3];

int solution()
{
	int result = INF;
	vector<vector<vector<int>>> dp(
		3, vector<vector<int>>(n + 1, vector<int>(3, INF)));

	// 첫번째 집을 color색깔로 칠하는 경우
	for (int color = 0; color < 3; color++)
		dp[color][0][color] = costs[0][color];

	// n번째 집까지 색칠
	for (int i = 1; i < n; i++)
	{
		for (int color = 0; color < 3; color++)
		{
			// n-1번째 집
			if (i < n - 1)
			{
				dp[0][i][color] = min(dp[0][i - 1][(color + 1) % 3], dp[0][i - 1][(color + 2) % 3]) + costs[i][color];
				dp[1][i][color] = min(dp[1][i - 1][(color + 1) % 3], dp[1][i - 1][(color + 2) % 3]) + costs[i][color];
				dp[2][i][color] = min(dp[2][i - 1][(color + 1) % 3], dp[2][i - 1][(color + 2) % 3]) + costs[i][color];
			}
			// 마지막 집
			else
			{
				if (color != 0)
					dp[0][i][color] = min(dp[0][i - 1][(color + 1) % 3], dp[0][i - 1][(color + 2) % 3]) + costs[i][color];
				if (color != 1)
					dp[1][i][color] = min(dp[1][i - 1][(color + 1) % 3], dp[1][i - 1][(color + 2) % 3]) + costs[i][color];
				if (color != 2)
					dp[2][i][color] = min(dp[2][i - 1][(color + 1) % 3], dp[2][i - 1][(color + 2) % 3]) + costs[i][color];
			}
		}
	}

	for (int s = 0; s < 3; s++)
	{
		for (int e = 0; e < 3; e++)
		{
			if (s == e) continue;
			result = min(result, dp[s][n - 1][e]);
		}
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> costs[i][0] >> costs[i][1] >> costs[i][2];

	cout << solution();
	return 0;
}