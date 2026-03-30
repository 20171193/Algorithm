// 백준 11053 - 가장 긴 증가하는 부분 수열 (s2)
#include <iostream>
#include <algorithm>
using namespace std;

// 최장 증가 수열 알고리즘
int n, ret, a[1001], dp[1001];

int BinarySearch(int l, int r, int n)
{
	int mid = -1;
	while (l < r)
	{
		mid = (l + r) / 2;
		if (dp[mid] >= n)
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}

	int cnt = 1;
	dp[1] = a[1];

	for (int i = 2; i <= n; i++)
	{
		if (dp[cnt] < a[i])
		{
			cnt++;
			dp[cnt] = a[i];
		}
		else
		{
			int temp = BinarySearch(1, cnt, a[i]);
			if (temp)
				dp[temp] = a[i];
		}
	}
	cout << cnt;
	return 0;
}