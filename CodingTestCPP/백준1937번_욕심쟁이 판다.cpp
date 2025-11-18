// 백준 1937번 : 욕심쟁이 판다(https://www.acmicpc.net/problem/1937)
// DFS, DP(거리 누적 방문처리)
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

int n, arr[501][501];

int dfs(int y, int x, vector<vector<int>>& visited)
{
	if (visited[y][x])
		return visited[y][x];

	visited[y][x] = 1;
	for (int d = 0; d < 4; d++)
	{
		int ny = y + dy[d];
		int nx = x + dx[d];
		if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
		if (arr[ny][nx] <= arr[y][x]) continue;

		visited[y][x] = max(visited[y][x], dfs(ny, nx, visited) + 1);
	}

	return visited[y][x];
}

int solution()
{
	int maxCount = 0;

	vector<vector<int>> visited(n, vector<int>(n));

	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			maxCount = max(maxCount, dfs(y, x, visited));

	return maxCount;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];

	cout << solution() << '\n';
	return 0;
}