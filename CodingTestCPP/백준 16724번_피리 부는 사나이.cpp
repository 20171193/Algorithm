// ���� 16724�� : �Ǹ� �δ� �糪��
// ����Ŭ ����
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

			// Ž��
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

			// ���� ����� ����Ŭ����
			if (visited[ny][nx] == VISITED)
				ret++;

			// �������
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