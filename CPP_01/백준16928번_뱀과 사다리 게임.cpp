// 백준 16928번 - 뱀과 사다리 게임
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, _map[101][101], edges[101], visited[101];

int bfs(int start, int dest)
{
	queue<int> q;
	visited[start] = 1;
	q.push(start);

	while (q.size())
	{
		int cur = q.front();
		q.pop();

		if (visited[dest] && visited[dest] <= visited[cur])
			continue;

		for (int i = 1; i <= 6; i++)
		{
			int next = cur + i;
			if (next > dest) continue;
			if (edges[next])
				next = edges[next];

			if (visited[next])
			{
				visited[next] = min(visited[next], visited[cur] + 1);
				continue;
			}

			visited[next] = visited[cur] + 1;
			q.push(next);
		}
	}

	return visited[dest] - 1;
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n + m; i++)
	{
		int s, e;
		cin >> s >> e;
		edges[s] = e;
	}

	cout << bfs(1, 100) << '\n';

	return 0;
}