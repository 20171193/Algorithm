// 백준 1197번 : 최소 스패닝 트리
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <tuple>
using namespace std;

int v, e;

class UnionFind
{
public:
	UnionFind() {}
	void Union(int a, int b, vector<int>& ranks, vector<int>& roots)
	{
		int pa = Find(a, roots);
		int pb = Find(b, roots);
		if (pa == pb)
			return;

		if (ranks[pa] == ranks[pb])
		{
			roots[pb] = pa;
			ranks[pa]++;
		}
		else if( ranks[pa] > ranks[pb])
			roots[pb] = pa;
		else // ranks[pa] < ranks[pb]
			roots[pa] = pb;
	}
	int Find(int a, vector<int>& roots)
	{
		if (roots[a] != a)
			roots[a] = Find(roots[a], roots);
		return roots[a];
	}
};

class Graph
{
private:
	int nodeCount;
	vector<tuple<int, int, int>> edges;
	vector<int> ranks, roots;
	UnionFind uf;
public:
	Graph(int nodeCount) : nodeCount(nodeCount), uf()
	{
		// 1-based
		ranks.assign(nodeCount + 1, 0);
		roots.assign(nodeCount + 1, 0);
		iota(roots.begin(), roots.end(), 0);
	}
	void AddEdge(int value, int start, int end)
	{
		edges.push_back(make_tuple(value, start, end));
	}
	int GetMSTValue()
	{
		// 가중치 기준 오름차
		sort(edges.begin(), edges.end());

		int mstValue = 0;
		int edgeCount = 0;

		for (const tuple<int, int, int>& edge : edges)
		{
			if (uf.Find(get<1>(edge), roots) != uf.Find(get<2>(edge), roots))
			{
				mstValue += get<0>(edge);
				edgeCount++;
				uf.Union(get<1>(edge), get<2>(edge), ranks, roots);
			}
		}

		if (edgeCount != nodeCount - 1)
			return -1;
		else
			return mstValue;
	}
};

int main()
{
	cin >> v >> e;

	Graph graph(v);
	for (int i = 0; i < e; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		graph.AddEdge(c, a, b);
	}

	cout << graph.GetMSTValue() << '\n';

	return 0;
}