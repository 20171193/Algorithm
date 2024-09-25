// 백준 11726번 2*n 타일링

#include <iostream>
using namespace std;

// dp[1] = | : 1
// dp[2] = ||,= : 2
// dp[3] = |||, =|, |= : 3
// dp[4] = ||||, =||, ||=, |=|, == : 5
// dp[5] = |||||, =|||, |||=, ||=|, |=||, ==|, |==, =|= : 8
// dp[6] = 13

int n, dp[1001];

int main()
{
	cin >> n;

	dp[0] = dp[1] = 1;
	for (int i = 2; i <= n; i++)
		dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;

	cout << dp[n] << '\n';

	return 0;
}