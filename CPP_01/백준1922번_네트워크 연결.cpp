// 백준 1922번 : 네트워크 연결
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Edge
{
	int s;
	int e;
	int v;
	Edge(int s, int e, int v) : s(s), e(e), v(v) {}
	bool operator<(const Edge& other) const
	{
		return v < other.v;
	}
};

int n, m;
vector<Edge> edges;

int Find(int a, vector<int>& root)
{
	if (a != root[a])
		root[a] = Find(root[a], root);

	return root[a];
}

void Union(int a, int b, vector<int>& rank, vector<int>& root)
{
	int ra = Find(a, root);
	int rb = Find(b, root);
	if (ra == rb) return;

	if (rank[ra] == rank[rb])
	{
		root[rb] = ra;
		rank[ra]++;
	}
	else if (rank[ra] > rank[rb])
		root[rb] = ra;
	else // rank[ra] < rank[rb]
		root[ra] = rb;
}

int main()
{
	cin >> n >> m;
	vector<int> rank(n + 1);
	vector<int> root(n + 1);
	iota(root.begin(), root.end(), 0);

	for (int i = 0; i < m; i++)
	{
		int s, e, v;
		cin >> s >> e >> v;
		edges.push_back({ s,e,v });
	}

	// 비용 기준 오름차 정렬
	sort(edges.begin(), edges.end());

	int cost = 0;
	for (const Edge& edge : edges)
	{
		if (Find(edge.s, root) != Find(edge.e, root))
		{
			Union(edge.s, edge.e, rank, root);
			cost += edge.v;
		}
	}

	cout << cost << '\n';

	return 0;
}