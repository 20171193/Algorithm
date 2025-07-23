// ���� 2293�� : ���� 1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;

int solution(const vector<int>& value)
{
	// k������ ����� ����� �� ��
	vector<int> dp(k + 1);

	dp[0] = 1;
	for (int v : value)
	{
		for (int i = v; i <= k; i++)
			dp[i] += dp[i - v];
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