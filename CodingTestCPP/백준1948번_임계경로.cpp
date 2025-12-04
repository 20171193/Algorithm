// 백준 1948번 : 임계경로 (https://www.acmicpc.net/problem/1948)
// 1. 가장 비싼 경로
// 
// 조건
//  - 도시(1<=n<=10,000)
//  - 도로(1<=m<=100,000)
//  - 시간(1<=w<=10,000)
// 
// 시도1. BFS(메모리초과)
//  => 해결 (모든 경로에 대한 비용을 계산할 필요 없음.)
//  : 위상정렬 방식으로 수정  
//  : 특정 노드에 대한 비용을 최대 비용으로 모두 갱신한 뒤 다음 깊이 탐색  
//  : BFS와 다르게 큐에 중복된 노드를 넣지 않음.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

pair<int, int> solution(int n, int s, int e, const vector<vector<pair<int, int>>>& edges)
{
	pair<int, int> ret = { 0,0 };

	vector<int> inDegree(n + 1, 0);
	for (int i = 1; i <= n; i++)
		for (auto& edge : edges[i])
			inDegree[edge.second]++;

	queue<int> q;
	vector<int> visited(n + 1);
	vector<vector<int>> prevs(n + 1);
	q.push(s);
	visited[s] = 0;
	prevs[s] = { -1 };

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (auto& edge : edges[cur])
		{
			inDegree[edge.second]--;

			int nextCost = visited[cur] + edge.first;
			if (visited[edge.second] < nextCost)
			{
				visited[edge.second] = nextCost;
				prevs[edge.second] = { cur };
			}
			else if (visited[edge.second] == nextCost)
				prevs[edge.second].push_back(cur);

			if (inDegree[edge.second] == 0)
				q.push(edge.second);
		}
	}

	ret.first = visited[e];

	visited.assign(n + 1, 0);
	q.push(e);
	visited[e] = 1;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		ret.second += prevs[cur].size();

		for (int prev : prevs[cur])
		{
			if (prev == -1) break;
			if (visited[prev]) continue;
			q.push(prev);
			visited[prev] = 1;
		}
	}

	ret.second--;
	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, u, v, w, s, e;
	cin >> n >> m;

	vector<vector<pair<int, int>>> edges(n + 1);
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		edges[u].push_back({ w, v });
	}
	cin >> s >> e;

	auto answer = solution(n, s, e, edges);
	cout << answer.first << '\n'
		<< answer.second << '\n';
	return 0;
}
