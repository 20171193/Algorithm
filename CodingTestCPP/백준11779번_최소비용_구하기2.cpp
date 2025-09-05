// 백준 11779번 : 최소비용 구하기 2
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

void solution(int n, int start, int end, const vector<vector<pair<int, int>>>& edges)
{
	vector<int> path(n + 1, -1);

	// 다익스트라
	vector<int> costs(n + 1, INT_MAX);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, start });

	while (!pq.empty())
	{
		int curCost = pq.top().first;
		int curNode = pq.top().second;
		pq.pop();

		if (curCost > costs[end])
			continue;

		for (auto edge : edges[curNode])
		{
			int to = edge.first;
			int cost = edge.second;

			int nextCost = cost + curCost;
			if (nextCost < costs[to])
			{
				costs[to] = nextCost;
				pq.push({ nextCost, to });
				// 경로 갱신
				path[to] = curNode;
			}
		}
	}

	// 경로 역추적
	vector<int> resultPath;

	int curNode = end;
	resultPath.push_back(curNode);
	while (path[curNode] != start)
	{
		curNode = path[curNode];
		resultPath.push_back(curNode);
	}
	resultPath.push_back(start);
	reverse(resultPath.begin(), resultPath.end());

	// 출력
	cout << costs[end] << '\n';
	cout << resultPath.size() << '\n';
	for (int p : resultPath)
		cout << p << ' ';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 0, m = 0, start = 0, end = 0;
	cin >> n >> m;
	vector<vector<pair<int, int>>> edges(n + 1);
	for (int i = 0; i < m; i++)
	{
		int s = 0, e = 0, c = 0;
		cin >> s >> e >> c;
		edges[s].push_back({ e, c });
	}
	cin >> start >> end;

	solution(n, start, end, edges);
	return 0;
}