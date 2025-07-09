// 백준 14938번 : 서강 그라운드
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 16;

int n, m, r;

struct Edge { int _endNode, _dist; };

struct comp
{
	bool operator()(const pair<int, int>& a, const pair<int, int>& b)
	{
		return a.second > b.second;
	}
};

// 다익스트라
vector<vector<int>> GetDist(const vector<vector<Edge>>& edges)
{
	vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

	priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;
	for (int startNode = 1; startNode <= n; startNode++)
	{
		dist[startNode][startNode] = 0;
		pq.push({ startNode,0 });

		while (!pq.empty())
		{
			int curNode = pq.top().first;
			int curDist = pq.top().second;
			pq.pop();

			for (const Edge& edge : edges[curNode])
			{
				int nextNode = edge._endNode;
				int nextDist = edge._dist + curDist;

				// 수색이 불가능한 영역은 미리 제거
				if (nextDist > m) continue;
				if (nextDist >= dist[startNode][nextNode]) continue;

				// 거리 갱신
				dist[startNode][nextNode] = nextDist;
				pq.push({ nextNode, nextDist });
			}
		}
	}

	return dist;
}

int solve(const vector<vector<Edge>>& edges, const vector<int>& items)
{
	vector<vector<int>> dist = GetDist(edges);

	int totalSum = 0;
	for (int i = 1; i <= n; i++)
	{
		int curSum = 0;
		for (int j = 1; j <= n; j++)
		{
			if (dist[i][j] > m) continue;
			curSum += items[j];
		}

		totalSum = max(totalSum, curSum);
	}
	return  totalSum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input (1-based)
	cin >> n >> m >> r;

	vector<int> items(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> items[i];

	vector<vector<Edge>> edges(n + 1);
	for (int i = 0; i < r; i++)
	{
		int s = 0, e = 0, c = 0;
		cin >> s >> e >> c;
		edges[s].push_back({ e , c });
		edges[e].push_back({ s, c });
	}

	cout << solve(edges, items) << '\n';
	return 0;
}