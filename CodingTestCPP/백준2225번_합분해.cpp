// ���� 2225�� : �պ���
#include <iostream>
#include <vector>
using namespace std;

constexpr int MOD = 1'000'000'000;

// *0�� �����ؾ� ��.
int solution(int n, int k)
{
	vector<vector<int>> dp(k + 1, vector<int>(n + 1));

	// i���� 0�� ����� ����� ��
	for (int i = 0; i <= k; i++)
		dp[i][0] = 1;

	// 1 <= k ���� ����� ����� �� 
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