// 백준 16724번 : 피리 부는 사나이
// 사이클 개수
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

enum Mark {
	SAFEZONE = -1,
	UNVISITED = 0,
	VISITED = 1
};

int n, m;
int visited[1001][1001];
string dir[1001];

int GetSafeZoneCount()
{
	int ret = 0;

	stack<pair<int, int>> path;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (visited[y][x] == SAFEZONE) continue;

			// 탐색
			int ny = y, nx = x;
			while (visited[ny][nx] == UNVISITED)
			{
				visited[ny][nx] = VISITED;
				path.push({ ny, nx });

				switch (dir[ny][nx])
				{
				case 'U': ny--; break;
				case 'D': ny++; break;
				case 'R': nx++; break;
				case 'L': nx--; break;
				default: break;
				}
			}

			// 현재 경로의 사이클인지
			if (visited[ny][nx] == VISITED)
				ret++;

			// 경로정리
			while (!path.empty())
			{
				visited[path.top().first][path.top().second] = SAFEZONE;
				path.pop();
			}
		}
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> dir[i];

	cout << GetSafeZoneCount() << '\n';

	return 0;
}