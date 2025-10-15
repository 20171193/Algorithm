// 백준 2156번 : 포도주 시식
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

// 6, 10, 13, 9, 8, 1

int solution(int n, const vector<int>& glasses)
{
	if (n <= 2)
		return accumulate(glasses.begin(), glasses.end(), 0);

	vector<int> dp(n + 1);
	dp[0] = 0;	// 아무것도 안먹는 경우
	dp[1] = glasses[1];
	dp[2] = glasses[1] + glasses[2];
	for (int i = 3; i <= n; i++)
	{
		// 1. i를 안뽑음
		// 2. i-1을 안뽑음
		// 3. i-1, i-2를 안뽑음
		dp[i] = max({
			dp[i - 1]
			, dp[i - 2] + glasses[i]
			, dp[i - 3] + glasses[i - 1] + glasses[i]
			});
	}

	return dp[n];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 0;
	cin >> n;

	// 1-based
	vector<int> glasses(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> glasses[i];

	cout << solution(n, glasses) << '\n';
	return 0;
}