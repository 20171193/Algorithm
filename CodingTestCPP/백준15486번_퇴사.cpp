// 백준 15486번 퇴사 2
#include <iostream>
#include <algorithm>
using namespace std;

int n, dp[1500001], arr[1500001][2];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i][0] >> arr[i][1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		// 상담을 할 수 없는 경우
		if (arr[i][0] + i > n)
			dp[i] = dp[i + 1];
		else
			dp[i] = max(dp[i + 1], arr[i][1] + dp[i + arr[i][0]]);
	}

	cout << dp[0] << '\n';

	return 0;
}