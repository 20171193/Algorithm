// 백준1699번 : 제곱수의 합(https://www.acmicpc.net/problem/1699)
// 항의 최소 개수
#include <iostream>
#include <algorithm>
using namespace std;

int n, dp[100001];

int main()
{
	cin >> n;

	dp[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		dp[i] = 17; // 2^17 = 120,000+
		for (int j = 1; j * j <= i; j++)
		{
			if (j * j == i)
			{
				dp[i] = 1;
				break;
			}
			else
				dp[i] = min(dp[i], dp[i - j * j] + 1);
		}
	}

	cout << dp[n] << '\n';
	return 0;
}