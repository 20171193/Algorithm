// 백준 20040번 : 사이클 게임
// union-find
#include <iostream>
#include <numeric>
using namespace std;

int n, m, root[500001];

int Find(int n)
{
	if (n != root[n])
		root[n] = Find(root[n]);
	return root[n];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	iota(root, root + n + 1, 0);

	int cycleTurn = 0;
	for (int i = 1; i <= m; i++)
	{
		int a, b;
		cin >> a >> b;

		int ra = Find(a);
		int rb = Find(b);
		if (ra != rb)
			root[rb] = ra;
		else if (cycleTurn == 0)
			cycleTurn = i;
	}

	cout << cycleTurn << '\n';
	return 0;
}