// 백준 16566번 - 카드 게임
// 카드를 사용할 때마다 재 정렬 x
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> 
using namespace std;

int n, m, k;
vector<int> selects, orders, greaters;

// 자신 혹은 큰 것
int Find(int num)
{
	if (greaters[num] != num)
		greaters[num] = Find(greaters[num]);

	return greaters[num];
}

void Union(int l, int r)
{
	int gl = Find(l);
	int gr = Find(r);
	greaters[gl] = gr;
}

// targetNum > oppNum
int SubmitGreaterCard(int oppNum)
{
	int _left = 0, _right = selects.size() - 1;

	while (_left <= _right)
	{
		int mid = (_left + _right) >> 1;

		if (selects[mid] <= oppNum)
			_left = mid + 1;
		else // selects[mid] > oppNum
			_right = mid - 1;
	}

	return _left == selects.size() ? Find(0) : Find(_left);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// input
	cin >> n >> m >> k;
	selects.assign(m, 0);
	greaters.assign(m, 0);
	iota(greaters.begin(), greaters.end(), 0);
	orders.assign(k, 0);

	for (int i = 0; i < m; i++)
		cin >> selects[i];
	for (int i = 0; i < k; i++)
		cin >> orders[i];

	// solve
	sort(selects.begin(), selects.end());

	for (int order : orders)
	{
		int idx = SubmitGreaterCard(order);

		// output
		cout << selects[idx] << '\n';

		if (idx < m - 1)
			Union(idx, idx + 1);
	}

	return 0;
}