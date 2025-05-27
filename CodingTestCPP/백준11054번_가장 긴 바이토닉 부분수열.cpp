// 백준 11054번 : 가장 긴 바이토닉 부분수열
#include <iostream>
#include <vector>
using namespace std;

int n, arr[1001];

int GetLISCount(int start, int end, bool greater = true)
{
	vector<int> lis;

	for (int cur = start; cur <= end; cur++)
	{
		int val = greater ? arr[cur] : -arr[cur];
		int pos = lower_bound(lis.begin(), lis.end(), val) - lis.begin();

		if (lis.size() == pos)
			lis.push_back(val);
		else
			lis[pos] = val;
	}

	return lis.size();
}

int solve()
{
	int result = 0;

	for (int i = 1; i < n - 1; i++)
	{
		int lc = GetLISCount(0, i);
		int rc = GetLISCount(i, n - 1, false);
		result = max(result, lc + rc - 1);
	}

	return result;
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