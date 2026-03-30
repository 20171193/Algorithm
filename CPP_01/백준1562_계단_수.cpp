// 백준 1562번 : 계단 수
#include <iostream>
using namespace std;

constexpr int MOD = 1000'000'000;

int n;

// 길이, 마지막 수, 비트마스킹
int dp[101][10][1 << 10];

int solution()
{
	dp[1][0][0] = 0;
	for (int num = 1; num <= 9; num++)
		dp[1][num][1 << num] = 1;

	for (int len = 2; len <= n; len++)
	{
		for (int num = 0; num <= 9; num++)
		{
			int numBit = 1 << num;
			for (int bit = 0; bit < (1 << 10); bit++)
			{
				dp[len][num][bit | numBit] =
					(dp[len][num][bit | numBit]
						+ (((num > 0 ? dp[len - 1][num - 1][bit] : 0)
							+ (num < 9 ? dp[len - 1][num + 1][bit] : 0)) % MOD)) % MOD;
			}
		}
	}

	int result = 0;
	for (int num = 0; num <= 9; num++)
		result = (result + dp[n][num][(1 << 10) - 1]) % MOD;

	return result;
}

int main()
{
	cin >> n;
	if (n < 10)
		cout << 0 << '\n';
	else
		cout << solution() << '\n';
	return 0;
}