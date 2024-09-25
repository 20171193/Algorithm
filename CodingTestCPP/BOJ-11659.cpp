// 백준 11659번 구간 합 구하기4 s4

#include <iostream>
using namespace std;

int n, m, a[100001], sums[100001];

int main()
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;

	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		sums[i] = sums[i - 1] + a[i];
	}

	for (int i = 0; i < m; i++)
	{
		int l = 0, r = 0, sum = 0;;
		cin >> l >> r;

		cout << sums[r] - sums[l - 1] << '\n';
	}

	return 0;
}