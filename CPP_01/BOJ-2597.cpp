// 백준 2579번 계단 오르기

// 한 번에 한 계단 또는 두 계단씩 오를 수 있음.
// 연속된 세 개의 계단을 모두 밟아서는 안 됨.
#include <iostream>
#include <algorithm>
using namespace std;

int n, a[301], dp[301];

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	dp[0] = a[0];
	dp[1] = max(a[0] + a[1], a[1]);

	for (int i = 2; i < n; i++)
	{
		dp[i] = max(dp[i - 2], dp[i - 2] + a[i - 1] + a[i]);
	}

	cout << dp[n - 1] << '\n';
	return 0;
}