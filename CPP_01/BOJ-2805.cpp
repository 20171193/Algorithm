// 백준 2805번 나무 자르기

#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, a[1000001];

ll Cut(int height)
{
	ll ret = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] <= height) continue;
		ret += a[i] - height;
	}
	return ret;
}
// 10 15 17 20
int BinarySearch(int l, int r)
{
	while (l <= r)
	{
		int mid = (ll)(l + r) / 2;
		ll sum = Cut(mid);

		// 조건 값 충족
		if (sum >= m)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return l - 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; i++)
		cin >> a[i];

	sort(a, a + n);

	cout << BinarySearch(0, a[n - 1]) << '\n';
	return 0;
}
