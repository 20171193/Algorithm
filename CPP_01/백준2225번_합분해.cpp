// 백준 2225번 : 합분해
#include <iostream>
#include <vector>
using namespace std;

constexpr int MOD = 1'000'000'000;

// *0도 포함해야 함.
int solution(int n, int k)
{
	vector<vector<int>> dp(k + 1, vector<int>(n + 1));

	// i개로 0을 만드는 경우의 수
	for (int i = 0; i <= k; i++)
		dp[i][0] = 1;

	// 1 <= k 개로 만드는 경우의 수 
	for (int count = 1; count <= k; count++)
		for (int num = 1; num <= n; num++)
			dp[count][num] = (dp[count - 1][num] + dp[count][num - 1] % MOD);

	return dp[k][n];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 0, k = 0;
	cin >> n >> k;

	cout << solution(n, k);

	return 0;
}