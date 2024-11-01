// ���� 2110�� ������ ��ġ
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

// �����⸦ �ִ��� �ָ� ��ġ�ؾ���.
// ���� ��ǥ�� �ִ� 10��
int n, c, ret, arr[200001];
// �Ÿ�����
set<int> dists;

// �Ÿ� �������� ���� ������ ��ġ
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
	// �Ÿ� �������� �����.
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