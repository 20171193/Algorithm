// 백준 2178번 미로 탐색

#include <iostream>
#include <queue>
using namespace std;

int n, m, a[101][101], visited[101][101];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

void bfs()
{
	queue<pair<int, int>> q;
	visited[0][0] = 1;
	q.push({ 0,0 });

	while (q.size())
	{
		pair<int, int> temp = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = dx[i] + temp.second;
			int ny = dy[i] + temp.first;

			if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
			if (a[ny][nx] == 0) continue;

			// 이미 방문한 경우
			if (visited[ny][nx])
			{
				visited[ny][nx] = min(visited[ny][nx], visited[temp.first][temp.second] + 1);
				continue;
			}
			else
				visited[ny][nx] = visited[temp.first][temp.second] + 1;

			q.push({ ny,nx });
		}
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		string temp = "";
		cin >> temp;
		for (int j = 0; j < temp.length(); j++)
			a[i][j] = temp[j] - '0';
	}

	bfs();

	cout << visited[n - 1][m - 1] << '\n';
	return 0;
}