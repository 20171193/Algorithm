// ���� 10844�� : ���� ��� ��
#include <iostream>
using namespace std;

constexpr int MOD = 1000000000;

int n;
// ����, ������ ��
int dp[101][10];

int solution()
{
	for (int num = 1; num <= 9; num++)
		dp[1][num] = 1;

	for (int len = 2; len <= n; len++)
	{
		dp[len][0] = dp[len - 1][1] % MOD;
		dp[len][9] = dp[len - 1][8] % MOD;
		for (int num = 1; num < 9; num++)
			dp[len][num] = (dp[len - 1][num - 1] + dp[len - 1][num + 1]) % MOD;
	}

	int result = 0;
	for (int num = 0; num <= 9; num++)
		result = (result + dp[n][num]) % MOD;
	return result;
}

int main()
{
	cin >> n;
	cout << solution();
	return 0;
}