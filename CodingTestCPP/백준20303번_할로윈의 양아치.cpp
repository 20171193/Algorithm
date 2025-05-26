// ���� 20303�� : �ҷ����� ���ġ
// Union-Find(union by size) + DP(�賶)
#include <iostream>
using namespace std;

int n, m, k;
int root[30001], dp[30001];
// ����� ��� ��, �� ���� ��
pair<int, int> infos[30001];

bool isRoot[30001];
void operator +=(pair<int, int>& a, const pair<int, int>& b)
{
	a.first += b.first; a.second += b.second;
}

// Union-Find
// : �ֻ��� ��Ʈ�� ����� ��� ��, ���� �� �Ҵ�
int Find(int a)
{
	if (a != root[a])
		root[a] = Find(root[a]);

	return root[a];
}
void UnionBySize(int lRoot, int sRoot)
{
	// ��Ʈ ��Ͽ��� ����
	isRoot[sRoot] = false;

	// �θ�� �Ҵ�
	infos[lRoot] += infos[sRoot];
	root[sRoot] = lRoot;
}
void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;
	if (infos[pa].first > infos[pb].first)
		UnionBySize(pa, pb);
	else
		UnionBySize(pb, pa);
}

// DP
// : �賶����
int StealCandy()
{
	for (int r = 1; r <= n; r++)
	{
		// ��Ʈ��常 Ȯ��
		if (!isRoot[r]) continue;

		int peopleCount = infos[r].first;
		int candyCount = infos[r].second;
		for (int p = k - 1; p >= peopleCount; --p)
			dp[p] = max(dp[p], dp[p - peopleCount] + candyCount);
	}

	return dp[k - 1];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
	{
		root[i] = i;
		isRoot[i] = true;
		// �ڽŵ� ����
		infos[i].first = 1;
		cin >> infos[i].second;
	}

	for (int i = 0; i < m; i++)
	{
		int s, e;
		cin >> s >> e;

		if (Find(s) != Find(e))
			Union(s, e);
	}

	cout << StealCandy() << '\n';

	return 0;
}