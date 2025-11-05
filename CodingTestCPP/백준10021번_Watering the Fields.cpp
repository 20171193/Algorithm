// 백준10021번 : Watering the Fields
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int distance(const pair<int, int>& a, const pair<int, int>& b)
{
	return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

int Find(int a, vector<int>& root)
{
	if (root[a] != a)
		root[a] = Find(root[a], root);
	return root[a];
}

bool Union(int a, int b, vector<int>& rank, vector<int>& root)
{
	int ra = Find(a, root);
	int rb = Find(b, root);

	if (ra == rb) return false;

	if (rank[ra] == rank[rb])
	{
		root[rb] = ra;
		rank[ra]++;
	}
	else if (rank[ra] > rank[rb])
		root[rb] = ra;
	else
		root[ra] = rb;
	return true;
}

struct Edge {
	int dist, na, nb;
};

int solution(int n, int c, const vector<pair<int, int>>& nodes)
{
	int answer = 0;

	vector<int> rank(n), root(n);
	iota(root.begin(), root.end(), 0);

	// 그리디하게 연결(비용기준 min-heap)
	vector<Edge> edges;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (i == j) continue;
			int dist = distance(nodes[i], nodes[j]);
			// 거리가 c이상일 경우만 설치
			if (dist < c) continue;
			edges.push_back({ dist, i, j });
		}
	}

	sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
		return a.dist < b.dist;
		});

	int edgeCount = 0;
	for (Edge& e : edges)
	{
		if (Union(e.na, e.nb, rank, root))
		{
			answer += e.dist;
			edgeCount++;
		}

		// MST의 간선은 총 N-1개
		if (edgeCount == n - 1)
			return answer;
	}

	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, c;
	cin >> n >> c;

	vector<pair<int, int>> nodes(n);
	for (int i = 0; i < n; i++)
		cin >> nodes[i].first >> nodes[i].second;

	cout << solution(n, c, nodes) << '\n';
	return 0;
}