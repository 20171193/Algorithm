// 백준 1865번 웜홀
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int INF = 987654321;
int tc, n, m, w, s, e, t;
// 음수 사이클 찾기
// 벨만포드

bool HasCycle(const unordered_map<int, vector<pair<int, int>>> edges)
{
	vector<int> dists(n + 1, INF);
	dists[1] = 0;

	// 연결 그래프가 아닐 수 있음
	// (탐색 과정에서 도달할 수 없었던 노드를 시작 노드로 설정)
	for (int i = 1; i <= n; i++)
	{
		if (dists[i] != INF)
			continue;
		dists[i] = 0;
		// n-1번 탐색
		for (int j = 1; j < n; j++)
		{
			// 간선이 없는경우
			if (edges.find(j) == edges.end()) continue;

			for (auto iter = edges.begin(); iter != edges.end(); iter++)
			{
				s = (*iter).first;
				// 경로가 없는 경우
				if (dists[s] == INF) continue;

				for (auto _iter = (*iter).second.begin(); _iter != (*iter).second.end(); _iter++)
				{
					e = (*_iter).first;
					t = (*_iter).second;

					dists[e] = min(dists[e], dists[s] + t);
				}
			}
		}
	}
	// 사이클 확인
	for (auto iter = edges.begin(); iter != edges.end(); iter++)
	{
		s = (*iter).first;
		// 경로가 없는 경우
		if (dists[s] == INF) continue;
		for (auto _iter = (*iter).second.begin(); _iter != (*iter).second.end(); _iter++)
		{
			e = (*_iter).first;
			t = (*_iter).second;

			// 음수 사이클 발견
			if (dists[e] > dists[s] + t)
				return true;
		}
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> tc;
	while (tc--)
	{
		cin >> n >> m >> w;

		// 도로 할당 (양방향)
		unordered_map<int, vector<pair<int, int>>> edges;
		for (int i = 0; i < m; i++)
		{
			cin >> s >> e >> t;
			if (edges.find(s) == edges.end())
				edges.insert({ s, {{e,t}} });
			else
				edges[s].push_back({ e,t });

			if (edges.find(e) == edges.end())
				edges.insert({ e, {{s,t}} });
			else
				edges[e].push_back({ s,t });

		}

		// 웜홀 할당 (단방향)
		for (int i = 0; i < w; i++)
		{
			cin >> s >> e >> t;
			if (edges.find(s) == edges.end())
				edges.insert({ s, {{e,-t}} });
			else
				edges[s].push_back({ e,-t });
		}

		if (HasCycle(edges))
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}

	return 0;
}