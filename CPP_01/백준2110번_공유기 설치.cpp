// 백준 2110번 공유기 설치
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

// 공유기를 최대한 멀리 설치해야함.
// 집의 좌표는 최대 10억
int n, c, ret, arr[200001];
// 거리모음
set<int> dists;

// 거리 기준으로 남은 공유기 설치
bool Build(int dist)
{
	int remain = c - 1;
	int prev = 0;
	for (int cur = 1; cur < n; cur++)
	{
		int curDist = arr[cur] - arr[prev];
		if (curDist < dist)
			continue;

		prev = cur;
		if (--remain <= 0)
			return true;
	}

	return false;
}

int BinarySearch()
{
	int l = 1;
	int r = arr[n - 1] - arr[0];

	while (l <= r)
	{
		int mid = (l + r) / 2;

		if (Build(mid))
			l = mid + 1;
		else
			r = mid - 1;
	}
	return r;
}

int solve()
{
	// 거리 기준으로 세우기.
	sort(arr, arr + n);

	return BinarySearch();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> c;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	cout << solve() << '\n';

	return 0;
}