// 백준 16236번 : 아기상어
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

constexpr int MAX_DISTANCE = 401;

int BFS(int& sy, int& sx, int size, int n, vector<vector<int>>& grid)
{
	// 우선순위 적용(*상-*좌-우-하)
	static constexpr int dx[4] = { 0, -1, 1, 0 };
	static constexpr int dy[4] = { -1, 0, 0, 1 };

	vector<vector<int>> visited(n, vector<int>(n, 0));
	queue<pair<int, int>> q;
	q.push({ sy,sx });

	int findY = n + 1, findX = n + 1;
	int shortestDist = MAX_DISTANCE;
	while (!q.empty())
	{
		auto cur = q.front();
		q.pop();

		if (visited[cur.first][cur.second] >= shortestDist)
			continue;

		for (int i = 0; i < 4; i++)
		{
			int ny = dy[i] + cur.first;
			int nx = dx[i] + cur.second;

			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			if (grid[ny][nx] == 0 || grid[ny][nx] == size)
			{
				if (visited[ny][nx] && visited[ny][nx] <= visited[cur.first][cur.second] + 1)
					continue;

				q.push({ ny,nx });
				visited[ny][nx] = visited[cur.first][cur.second] + 1;
			}
			else if (grid[ny][nx] != 0 && grid[ny][nx] < size)
			{
				int curDist = visited[cur.first][cur.second] + 1;

				if (curDist <= shortestDist)
				{
					if (ny > findY) continue;

					if (ny < findY || (ny == findY && nx < findX))
					{
						shortestDist = curDist;
						findY = ny;
						findX = nx;
					}
					continue;
				}
			}
		}
	}

	if (shortestDist == MAX_DISTANCE)
		return -1;

	grid[findY][findX] = 0;
	sy = findY, sx = findX;
	return shortestDist;
}

int solution(int n, int sy, int sx, vector<vector<int>>& grid)
{
	int totalDist = 0;
	int curSize = 2, eatCount = 0;

	grid[sy][sx] = 0;
	while (true)
	{
		int getDist = BFS(sy, sx, curSize, n, grid);

		if (getDist == -1)
			break;
		else
			totalDist += getDist;


		if (++eatCount == curSize)
		{
			curSize++;
			eatCount = 0;
		}
	}

	return totalDist;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 0;
	cin >> n;

	int sy = -1, sx = -1;
	vector<vector<int>> grid(n, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> grid[i][j];
			if (grid[i][j] == 9)
			{
				sy = i;
				sx = j;
			}
		}
	}

	cout << solution(n, sy, sx, grid);
	return 0;
}