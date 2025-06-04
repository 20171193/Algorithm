// 백준 10775번 : 공항
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

const int MAX_GATE = 100001;

int g, p, input[MAX_GATE], linked[MAX_GATE];

int Find(int a)
{
	// 경로 압축
	if (linked[a] != a)
		linked[a] = Find(linked[a]);

	return linked[a];
}

int solve()
{
	iota(linked, linked + g + 1, 0);

	int count = 0;
	for (count; count < p; count++)
	{
		int des = input[count];
		int lnk = Find(des);

		if (lnk == 0) break;

		linked[lnk] = lnk - 1;
	}

	return count;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> g >> p;
	for (int i = 0; i < p; i++)
		cin >> input[i];

	cout << solve() << '\n';

	return 0;
}