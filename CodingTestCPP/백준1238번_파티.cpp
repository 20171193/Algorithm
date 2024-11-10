// 백준1238번 파티

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 987654321;
int n, m, x;
struct comparer {
	bool operator()(const pair<int, int>& a, const pair<int, int>& b)
	{
		return a.first < a.second;
	}
};
vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& edge)
{
	vector<int> visited(n + 1, INF);
	visited[start] = 0;

	// 현재 노드에서 가장 가까운 순으로 
	// value, node
	priority_queue<pair<int, int>, vector<pair<int, int>>, comparer> pq;

	pq.push({ visited[start], start });
	while (pq.size())
	{
		int curDist = pq.top().first;
		int curNode = pq.top().second;
		pq.pop();

		// 최단거리로 갱신된 경로라면 무시
		if (curDist > visited[curNode])
			continue;

		for (int i = 0; i < edge[curNode].size(); i++)
		{
			int next = edge[curNode][i].first;
			int value = edge[curNode][i].second;

			if (visited[next] <= curDist + value)
				continue;

			visited[next] = curDist + value;
			pq.push({ visited[next], next });
		}
	}

	return visited;
}

int main()
{
	cin >> n >> m >> x;
	vector<vector<pair<int, int>>> edges(n + 1);
	// 타 노드들에서 특정 노드까지의 최단거리를 구하기 위함
	vector<vector<pair<int, int>>> reverseEdges(n + 1);
	for (int i = 0; i < m; i++)
	{
		int s, e, t;
		cin >> s >> e >> t;
		edges[s].push_back({ e,t });
		reverseEdges[e].push_back({ s,t });
	}

	int distToParty = 0;
	int ret = 0;
	// 파티에서 집까지 거리
	vector<int> toHomes = dijkstra(x, edges);
	// 각 집에서 파티까지의 거리
	vector<int> toParty = dijkstra(x, reverseEdges);
	for (int i = 1; i <= n; i++)
	{
		if (i == x) continue;

		// 거리 합
		int sum = toHomes[i] + toParty[i];
		if (ret < sum)
			ret = sum;
	}

	cout << ret << '\n';

	return 0;
}