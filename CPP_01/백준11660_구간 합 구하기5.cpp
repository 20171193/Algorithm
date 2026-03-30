// 백준 11660번 구간 합 구하기 5

// M = 100,000 -> 누적합으로 풀기
#include <iostream>
using namespace std;

typedef long long ll;

int n, m, arr[1025][1025];
ll sum[1025][1025];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int x = 1; x <= n; x++)
	{
		for (int y = 1; y <= n; y++)
		{
			cin >> arr[x][y];
			if (x == 1 && y > 1)
				sum[x][y] = sum[x][y - 1] + arr[x][y];
			else if (y == 1 && x > 1)
				sum[x][y] = sum[x - 1][y] + arr[x][y];
			else if (x == 1 && y == 1)
				sum[x][y] = arr[x][y];
			else
				sum[x][y] = sum[x][y - 1] + sum[x - 1][y] + arr[x][y] - sum[x - 1][y - 1];
		}
	}

	for (int i = 0; i < m; i++)
	{
		int mnX = 0, mnY = 0, mxX = 0, mxY = 0;
		cin >> mnX >> mnY >> mxX >> mxY;

		ll temp = sum[mxX][mxY];

		if (mnX > 1 && mnY > 1)
		{
			temp -= sum[mxX][mnY - 1];
			temp -= sum[mnX - 1][mxY];
			temp += sum[mnX - 1][mnY - 1];
		}
		else if (mnX > 1)
		{
			temp -= sum[mnX - 1][mxY];
		}
		else if (mnY > 1)
		{
			temp -= sum[mxX][mnY - 1];
		}

		cout << temp << '\n';
	}

	return 0;
}