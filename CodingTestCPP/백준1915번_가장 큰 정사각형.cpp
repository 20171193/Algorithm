// 백준 1915번 : 가장 큰 정사각형
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 정사각형 DP
int solution(int n, int m, const vector<string>& arr)
{
	vector<vector<int>> dp(n, vector<int>(m));
	int maxSegment = 0;

	// 메모이제이션
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (arr[y][x] == '0') continue;

			if (y == 0 || x == 0)
				dp[y][x] = 1;
			else
				dp[y][x] = min({ dp[y - 1][x], dp[y][x - 1], dp[y - 1][x - 1] }) + 1;

			maxSegment = max(dp[y][x], maxSegment);
		}
	}

	return maxSegment * maxSegment;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input
	int n = 0, m = 0;
	cin >> n >> m;

	vector<string> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	// output
	cout << solution(n, m, arr) << '\n';

	return 0;
}