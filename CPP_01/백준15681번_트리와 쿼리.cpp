// 백준 15681번 : 트리와 쿼리
#include <iostream>
#include <vector>
using namespace std;

int n, r, q;

int dfs(int node, const vector<vector<int>>& edge, vector<int>& counts)
{
	// 자기자신 포함, 마킹
	counts[node] = 1;

	for (int next : edge[node])
	{
		// 마킹된 노드 continue
		if (counts[next])
			continue;
		counts[node] += dfs(next, edge, counts);
	}

	return counts[node];
}

vector<int> solution(const vector<vector<int>>& edge, const vector<int>& query)
{
	vector<int> answer(query.size());

	vector<int> counts(n + 1);
	dfs(r, edge, counts);

	for (int i = 0; i < query.size(); i++)
		answer[i] = counts[query[i]];

	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> r >> q;
	vector<vector<int>> edge(n + 1);
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}

	vector<int> query(q);
	for (int i = 0; i < q; i++)
		cin >> query[i];

	// output
	for (int ans : solution(edge, query))
		cout << ans << '\n';

	return 0;
}