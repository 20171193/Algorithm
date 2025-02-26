// 백준 1707번 - 이분 그래프
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int k, v, e;
vector<string> answer;

bool BFS(int node, vector<int>& visited, const vector<vector<int>>& edges)
{
	queue<int> q;
	q.push(node);
	visited[node] = 1;

	while (q.size())
	{
		int cur = q.front();
		q.pop();

		for (int i = 0; i < edges[cur].size(); i++)
		{
			int next = edges[cur][i];
			if (visited[next] == visited[cur])
				return false;
			else if (visited[next] == 0)
			{
				q.push(next);
				visited[next] = -visited[cur];
			}
			else
				continue;
		}
	}
	return true;
}

bool solution(const vector<vector<int>>& edges)
{
	vector<int> visited(v + 1, 0);

	for (int i = 1; i <= v; i++)
	{
		if (visited[i] != 0) continue;

		if (!BFS(i, visited, edges))
			return false;
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> k;
	while (k--)
	{
		cin >> v >> e;
		vector<vector<int>> edges(v + 1);
		for (int i = 0; i < e; i++)
		{
			int u, v;
			cin >> u >> v;
			edges[u].push_back(v);
			edges[v].push_back(u);
		}

		if (solution(edges))
			answer.push_back("YES");
		else
			answer.push_back("NO");
	}

	for (string ans : answer)
		cout << ans << '\n';

	return 0;
}