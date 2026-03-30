// 백준 11722번 : 가장 긴 감소하는 부분 수열
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, arr[1001];

int solve()
{
	vector<int> dp;
	reverse(arr, arr + n);

	for (int i = 0; i < n; i++)
	{
		int val = arr[i];
		int pos = lower_bound(dp.begin(), dp.end(), val) - dp.begin();

		if (pos == dp.size())
			dp.push_back(val);
		else
			dp[pos] = val;
	}
	return dp.size();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	cout << solve() << '\n';
	return 0;
}