// 백준 1647번 : 도시 분할 계획
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Edge
{
	int s, e, v;
	bool operator<(const Edge& other) const
	{
		return v < other.v;
	}
};

int n, m;
vector<int> root, ufRank;
vector<Edge> edges;

int Find(int a)
{
	if (root[a] != a)
		root[a] = Find(root[a]);
	return root[a];
}

void Union(int a, int b)
{
	int ra = Find(a);
	int rb = Find(b);

	if (ra == rb) return;

	if (ufRank[ra] == ufRank[rb])
	{
		root[rb] = ra;
		ufRank[ra]++;
	}
	else if (ufRank[ra] > ufRank[rb])
		root[rb] = ra;
	else
		root[ra] = rb;
}

int main()
{
	cin >> n >> m;

	ufRank.assign(n + 1, 0);
	root.assign(n + 1, 0);
	iota(root.begin(), root.end(), 0);

	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		edges.push_back({ a,b,c });
	}

	sort(edges.begin(), edges.end());

	int cost = 0;
	int edgeCount = 0;
	for (const Edge& edge : edges)
	{
		int s = edge.s;
		int e = edge.e;
		int v = edge.v;
		if (Find(s) != Find(e))
		{
			Union(s, e);

			edgeCount++;
			// 가장 비싸게 연결되는 간선을 제거 (도시 분할)
			if (edgeCount == n - 1)
				break;
			cost += v;
		}
	}

	cout << cost << '\n';

	return 0;
}
