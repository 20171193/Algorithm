// 백준 2887번 - 행성 터널
// mst
// - n*(n+1)/2 (간선 입력만 50억 이상)
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

typedef long long ll;

const int X = 0, Y = 1, Z = 2, INDEX = 3;

struct Edge
{
	int s, e, v;
	bool operator<(const Edge& other) const
	{
		return v < other.v;
	}
};

int n;
ll ret = 0;
vector<vector<int>> inputs;
vector<int> ufRank, root;

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

	if (ufRank[ra] >= ufRank[rb])
	{
		root[rb] = ra;

		if (ufRank[ra] == ufRank[rb])
			ufRank[ra]++;
	}
	else
		root[ra] = rb;
}


int main()
{
	// input
	cin >> n;

	ufRank.assign(n, 0);
	root.assign(n, 0);
	inputs.assign(n, vector<int>(4));

	for (int i = 0; i < n; i++)
	{
		cin >> inputs[i][X] >> inputs[i][Y] >> inputs[i][Z];
		inputs[i][INDEX] = i;
		root[i] = i;
	}

	// solve
	for (int axis = 0; axis < 3; axis++)
	{
		// 축 기준 정렬
		sort(inputs.begin(), inputs.end(),
			[axis](const vector<int>& a, const vector<int>& b) { return a[axis] < b[axis]; });

		for (int i = 0; i < n - 1; i++)
			edges.push_back({ inputs[i][INDEX], inputs[i + 1][INDEX], inputs[i + 1][axis] - inputs[i][axis] });
	}

	sort(edges.begin(), edges.end());
	int edgeCount = 0;
	for (const Edge& edge : edges)
	{
		if (Find(edge.s) == Find(edge.e)) continue;

		Union(edge.s, edge.e);
		ret += edge.v;
		edgeCount++;

		if (edgeCount == n - 1)
			break;
	}

	// output
	cout << ret << '\n';

	return 0;
}