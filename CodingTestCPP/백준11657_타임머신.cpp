// ���� 11657�� Ÿ�Ӹӽ�

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <memory.h>
#include <limits>
using namespace std;

// �������� �˰��� 
// - �� �������� �ٸ� ��� ������ �̸��� �ִ� ��� One to All
// - ���� ����ġ�� ������ ����
// - ���� ����Ŭ�� ��� -1 ���
// - O(N*M), 3,000,000

typedef long long ll;
int n, m, a, b, c;
map<pair<int, int>, int> graph;
const ll MaxDist = numeric_limits<ll>::max();

// Ž���� �Բ� ����Ŭ �����Ǵ�
bool HasCycle(int start, vector<ll>& dists)
{
	// start �������� �Ÿ��� �ִ� �Ÿ��� �ʱ�ȭ
	dists[start] = 0;

	// ���� Ž�� (�Ÿ� ����)
	for (int i = 1; i < n; i++) {
		for (auto iter = graph.begin(); iter != graph.end(); iter++)
		{
			auto& edge = *iter;
			int s = edge.first.first;	// ���� ���
			int e = edge.first.second;	// �� ���
			int v = edge.second;		// ���� ����ġ

			if (dists[s] == MaxDist) continue;
			dists[e] = min(dists[e], dists[s] + v);
		}
	}

	// ���� ����Ŭ Ȯ��
	for (auto iter = graph.begin(); iter != graph.end(); iter++)
	{
		auto& edge = *iter;
		int s = edge.first.first;	// ���� ���
		int e = edge.first.second;	// �� ���
		int v = edge.second;		// ���� ����ġ

		if (dists[s] == MaxDist) continue;
		// ���� Ž�� �Ÿ����� �ִܰŸ��� ã�� ��� (���� ����Ŭ)
		if (dists[e] > dists[s] + v)
			return true;
	}
	return false;
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		if (graph.find({ a,b }) == graph.end())
			graph[{a, b}] = c;
		else
			graph[{a, b}] = min(graph[{a, b}], c);
	}

	vector<ll> dists(n + 1, MaxDist);
	bool hasCycle = HasCycle(1, dists);

	if (hasCycle)
		cout << -1 << '\n';
	else
	{
		for (int i = 2; i <= n; i++)
		{
			if (dists[i] == MaxDist)
				cout << -1 << '\n';
			else
				cout << dists[i] << '\n';
		}
	}

	return 0;
}