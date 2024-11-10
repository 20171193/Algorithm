// ���� 1167�� Ʈ���� ����

#include <iostream>
#include <vector>
#include <memory.h>
#include <math.h>
using namespace std;

bool visited[100001];
int v, farNode, maxDist;

void dfs(int cur, int dist, const vector<vector<pair<int, int>>>& tree)
{
	if (dist > maxDist)
	{
		farNode = cur;
		maxDist = dist;
	}

	visited[cur] = true;

	for (const auto& edge : tree[cur])
	{
		int next = edge.first;
		int value = edge.second;

		if (visited[next]) continue;

		dfs(next, dist + value, tree);
	}
}

int main()
{
	cin >> v;
	vector<vector<pair<int, int>>> tree(v + 1);

	for (int i = 0; i < v; i++)
	{
		int s, e, v;
		cin >> s;
		while (1)
		{
			cin >> e;
			if (e == -1) break;
			cin >> v;
			tree[s].push_back({ e,v });
		}
	}

	// �ƹ� ��忡�� ���� �� ��� ã��
	dfs(1, 0, tree);

	memset(visited, false, v + 1);

	// ã�� ��忡�� �ݴ��� ���� �� ��� ã��
	dfs(farNode, 0, tree);

	cout << maxDist << '\n';

	return 0;
}