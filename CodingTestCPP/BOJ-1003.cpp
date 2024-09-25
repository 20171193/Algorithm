// 백준 1003번 피보나치 함수

#include <iostream>
using namespace std;

int t;
pair<int, int> dp[41];

pair<int, int> operator+(pair<int, int>& a, pair<int, int>& b)
{
	return { a.first + b.first, a.second + b.second };
}
int main()
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	dp[0] = { 1, 0 };
	dp[1] = { 0, 1 };
	for (int i = 2; i < 41; i++)
		dp[i] = dp[i - 2] + dp[i - 1];


	cin >> t;
	while (t--)
	{
		int n = 0;
		cin >> n;
		cout << dp[n].first << ' ' << dp[n].second << '\n';
	}


	return 0;
}