//백준 1654번 랜선 자르기
#include <iostream>
#include <algorithm>
using namespace std;

// 주어진 랜선들을 잘라서 n개의 랜선을 만들어야함.
typedef long long ll;
int n, k;
ll arr[1000001];

int Cut(int num)
{
	if (num == 0) return 0;
	int ret = 0;

	for (int i = 0; i < k; i++)
		ret += arr[i] / num;

	return ret;
}

int BinarySearch()
{
	ll l = 1;
	ll r = arr[k - 1];

	while (l <= r)
	{
		ll mid = (l + r) / 2;

		if (Cut(mid) >= n)
			l = mid + 1;
		else
			r = mid - 1;
	}

	return r;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> k >> n;
	for (int i = 0; i < k; i++)
		cin >> arr[i];

	sort(arr, arr + k);

	cout << BinarySearch() << '\n';

	return 0;
}
