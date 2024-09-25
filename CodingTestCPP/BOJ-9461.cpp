// 백준 9461번 파도반 수열
// f(x) = f(x-3) + f(x-2)

#include <iostream>
#include <vector>
using namespace std;

int t;
long long dp[101];

int main()
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	dp[0] = dp[1] = dp[2] = 1;

	for (int i = 3; i <= 100; i++)
		dp[i] = dp[i - 3] + dp[i - 2];

	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		cout << dp[n - 1] << '\n';
	}

	return 0;
}