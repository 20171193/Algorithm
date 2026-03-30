// 백준 2448번 : 별 찍기 11
#include <iostream>
using namespace std;

bool grid[3200][6200];

void go(int y, int x, int n)
{
	if (n == 3)
	{
		grid[y][x] = true;
		grid[y + 1][x - 1] = grid[y + 1][x + 1] = true;
		for (int i = -2; i <= 2; i++)
			grid[y + 2][x + i] = true;
		return;
	}

	int m = n / 2;
	go(y, x, m);
	go(y + m, x - m, m);
	go(y + m, x + m, m);
}

int main()
{
	ios::sync_with_stdio(false);
	cout.tie(NULL);

	int n = 0;
	cin >> n;

	go(0, n - 1, n);
	for (int y = 0; y < n; y++)
	{
		string str;
		for (int x = 0; x < 2 * n - 1; x++)
			str += grid[y][x] ? '*' : ' ';
		cout << str << '\n';
	}
	return 0;
}