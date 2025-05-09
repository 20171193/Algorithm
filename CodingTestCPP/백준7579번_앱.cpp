// ���� 7579�� : ��
// �賶����
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 10001;

int n, m, minCost = INF, dp[INF];
pair<int, int> apps[101];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//input
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> apps[i].first;
	for (int i = 0; i < n; i++)
		cin >> apps[i].second;

	//solve
	for (int i = 0; i < n; i++)
	{
		int curMemory = apps[i].first;
		int curCost = apps[i].second;
		// ������ ��� ��� Ž��
		for (int c = INF - 1; c >= curCost; c--)
		{
			dp[c] = max(dp[c], dp[c - curCost] + curMemory);
			if (dp[c] >= m && c < minCost)
				minCost = c;
		}
	}

	//output
	cout << minCost << '\n';

	return 0;
}