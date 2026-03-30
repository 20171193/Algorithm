// ¹éÁØ 11049¹ø : Çà·Ä °ö¼À ¼ø¼­
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int solution(const vector<pair<int, int>>& matrix)
{
	int size = matrix.size();
	vector<vector<int>> dp(size, vector<int>(size, 0));

	for (int len = 2; len <= size; len++)
	{
		for (int s = 0; s <= size - len; s++)
		{
			int e = s + len - 1;
			dp[s][e] = INT_MAX;
			for (int m = s; m < e; m++)
			{
				// s-m + (m+1)-e
				int cost = matrix[s].first * matrix[m].second * matrix[e].second;
				dp[s][e] = min(dp[s][e], dp[s][m] + dp[m + 1][e] + cost);
			}
		}
	}

	return dp[0][size - 1];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input
	int n = 0;
	cin >> n;

	vector<pair<int, int>> matrix(n);
	for (int i = 0; i < n; i++)
		cin >> matrix[i].first >> matrix[i].second;

	// output
	cout << solution(matrix) << '\n';

	return 0;
}