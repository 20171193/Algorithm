// 백준 1520번 - 내리막 길
#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int m, n, _map[501][501], dp[501][501];

int dfs(int y, int x)
{
	if (dp[y][x] != -1)
		return dp[y][x];

	if (y == m - 1 && x == n - 1)
		return 1;

	dp[y][x] = 0;
	for (int i = 0; i < 4; i++)
	{
		int nx = dx[i] + x;
		int ny = dy[i] + y;
		if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		if (_map[ny][nx] >= _map[y][x]) continue;

		dp[y][x] += dfs(ny, nx);
	}

	return dp[y][x];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> m >> n;
	for (int i = 0; i < m; i++)
	{
		memset(dp[i], -1, sizeof(int) * n);
		for (int j = 0; j < n; j++)
			cin >> _map[i][j];
	}


	cout << dfs(0, 0) << '\n';

	return 0;
}