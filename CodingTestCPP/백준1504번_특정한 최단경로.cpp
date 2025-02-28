// 백준 1504번 - 특정한 최단 경로
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 987654321;
int n, e, wp1, wp2;


struct Edge {
	int to;
	int cost;
	Edge(int to, int cost) : to(to), cost(cost) {}
};

struct comparer
{
	bool operator()(const Edge& a, const Edge& b)
	{
		return a.cost > b.cost;
	}
};


vector<int> Dijkstra(int start, const vector<vector<Edge>>& edges)
{
	vector<int> dists(n + 1, INF);
	dists[start] = 0;

	priority_queue<Edge, vector<Edge>, comparer> pq;
	pq.push(Edge(start, 0));

	while (!pq.empty())
	{
		int curNode = pq.top().to;
		int curCost = pq.top().cost;
		pq.pop();

		if (curCost > dists[curNode])
			continue;

		for (int i = 0; i < edges[curNode].size(); i++)
		{
			int nextNode = edges[curNode][i].to;
			int nextCost = edges[curNode][i].cost;

			if (curCost + nextCost >= dists[nextNode])
				continue;

			dists[nextNode] = dists[curNode] + nextCost;
			pq.push(Edge(nextNode, dists[nextNode]));
		}
	}

	return dists;
}

int main()
{
	cin >> n >> e;
	vector<vector<Edge>> edges(n + 1);
	for (int i = 0; i < e; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	cin >> wp1 >> wp2;

	vector<int> sDists = Dijkstra(1, edges);
	vector<int> wp1Dists = Dijkstra(wp1, edges);
	vector<int> wp2Dists = Dijkstra(wp2, edges);

	if (sDists[wp1] == INF || sDists[wp2] == INF || wp1Dists[wp2] == INF || wp1Dists[n] == INF)
		cout << -1 << '\n';
	else
		cout << min(sDists[wp1] + wp1Dists[wp2] + wp2Dists[n], sDists[wp2] + wp2Dists[wp1] + wp1Dists[n]);


	return 0;
}