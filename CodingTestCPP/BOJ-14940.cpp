// 백준 14940번 쉬운 최단거리

#include <iostream>
#include <queue>
using namespace std;

int n, m, a[1001][1001], visited[1001][1001];
pair<int, int> start;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

// 도착점으로 부터 BFS 거리 누적
void BFS()
{
	queue<pair<int, int>> q;
	visited[start.first][start.second] = 0;
	q.push(start);

	while (q.size())
	{
		pair<int, int> temp = q.front(); q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = dx[i] + temp.second;
			int ny = dy[i] + temp.first;

			if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
			if (!a[ny][nx]) continue;
			if (visited[ny][nx])
			{
				visited[ny][nx] = min(visited[ny][nx], visited[temp.first][temp.second] + 1);
				continue;
			}

			visited[ny][nx] = visited[temp.first][temp.second] + 1;
			q.push({ ny,nx });
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cin >> a[y][x];
			if (a[y][x] == 2)
				start = { y,x };
		}
	}

	BFS();

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			// 최초 위치는 0 출력
			if (make_pair(y, x) == start)
			{
				cout << 0 << ' ';
				continue;
			}
			// 원래 갈 수 있는 땅인 부분 중 도달할 수 없는 위치
			if (!visited[y][x] && a[y][x])
			{
				// 즉, 방문체크가 되지 않았으면서 땅인 위치
				cout << -1 << ' ';
				continue;
			}

			cout << visited[y][x] << ' ';
		}
		cout << '\n';
	}

	return 0;
}