// ���� 2294�� : ���� 2
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;

int solution(vector<int>& value)
{
	// ������ �ּ� ������
	vector<int> dp(k + 1, -1);

	sort(value.begin(), value.end());
	dp[0] = 0;

	for (int v : value)
	{
		for (int i = v; i <= k; i++)
		{
			if (dp[i - v] == -1) continue;

			if (dp[i] == -1)
				dp[i] = dp[i - v] + 1;
			else // ����
				dp[i] = min(dp[i - v] + 1, dp[i]);
		}
	}

	return dp[k];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;
	vector<int> value(n);

	for (int i = 0; i < n; i++)
		cin >> value[i];

	cout << solution(value) << '\n';

	return 0;
}