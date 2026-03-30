// 백준1328번 : 고층 빌딩
// 빌딩의 높이는 서로 다름
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>
using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

map<tuple<int, int, int>, ll> dp;

int solution(int n, int l, int r)
{
	if (n == 0 || l == 0 || r == 0) return 0;
	if (n == 1) return (l == 1 && r == 1) ? 1 : 0;

	auto key = make_tuple(n, l, r);
	if (dp.find(key) != dp.end())
		return dp[key];

	// 가장 높은 빌딩을 기준으로
	// 나머지 빌딩을 배치하는 경우의 수
	ll left = 0, right = 0, mid = 0;
	// ex) 5
	if (l > 0)	// 5 . . . .
		left = solution(n - 1, l - 1, r);
	if (r > 0)	// . . . . 5
		right = solution(n - 1, l, r - 1);
	if (n > 2)	// . . 5 . .
		mid = solution(n - 1, l, r) % MOD * (n - 2);

	ll res = ((left + right) % MOD + mid) % MOD;
	dp[key] = res;

	return res;
}

int main()
{
	int n = 0, l = 0, r = 0;
	cin >> n >> l >> r;

	cout << solution(n, l, r) << '\n';
	return 0;
}