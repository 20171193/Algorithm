// 백준 20303번 : 할로윈의 양아치
// Union-Find(union by size) + DP(배낭)
#include <iostream>
using namespace std;

int n, m, k;
int root[30001], dp[30001];
// 연결된 노드 수, 총 사탕 수
pair<int, int> infos[30001];

bool isRoot[30001];
void operator +=(pair<int, int>& a, const pair<int, int>& b)
{
	a.first += b.first; a.second += b.second;
}

// Union-Find
// : 최상위 루트에 연결된 사람 수, 사탕 수 할당
int Find(int a)
{
	if (a != root[a])
		root[a] = Find(root[a]);

	return root[a];
}
void UnionBySize(int lRoot, int sRoot)
{
	// 루트 목록에서 제거
	isRoot[sRoot] = false;

	// 부모로 할당
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
// : 배낭문제
int StealCandy()
{
	for (int r = 1; r <= n; r++)
	{
		// 루트노드만 확인
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
		// 자신도 포함
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