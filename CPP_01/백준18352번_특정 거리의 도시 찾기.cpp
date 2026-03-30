// 백준 18352번 : 특정 거리의 도시 찾기(https://www.acmicpc.net/problem/18352)
// 1. 단방향 도로
// 2. 거리는 1
// 3. x출발 최단 거리가 k인 모든 도시의 번호
// 4. BFS 최단거리 탐색
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, k, x;
vector<vector<int>> edges;

vector<int> solution()
{
	vector<int> answer, visited(n + 1);
	queue<int> q;
	q.push(x);
	visited[x] = 1;

	while (!q.empty())
	{
		int cur = q.front(); q.pop();
		for (int i = 0; i < edges[cur].size(); i++)
		{
			int next = edges[cur][i];
			if (visited[next])
			{
				if (visited[next] > visited[cur] + 1)
					visited[next] = visited[cur] + 1;
				continue;
			}

			q.push(next);
			visited[next] = visited[cur] + 1;
		}
	}

	for (int i = 1; i <= n; i++)
		if (visited[i] == k + 1)
			answer.push_back(i);

	return answer;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> k >> x;
	edges.assign(n + 1, vector<int>());

	for (int i = 0; i < m; i++)
	{
		int s, e;
		cin >> s >> e;
		edges[s].push_back(e);
	}

	vector<int> answer = solution();
	if (answer.size() == 0)
		cout << -1 << '\n';
	else
	{
		sort(answer.begin(), answer.end());
		for (int ans : answer)
			cout << ans << '\n';
	}
	return 0;
}