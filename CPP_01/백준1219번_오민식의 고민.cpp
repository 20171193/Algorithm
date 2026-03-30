
// 백준 1219번 : 오민식의 고민(https://www.acmicpc.net/problem/1219)
//
// 조건
//  1. 획득비용 : 판매비용 - 도로비용
//  2. 도착 불가능 "gg"
//  3. 도착 가능
//   3-1. 경로 중 양수 사이클 발견 시 "Gee"
//   3-2. 최장 거리
// 
// 풀이
//  1. 벨만포드 : 시작지점 -> 도착지점 경로 확인 + 양수 사이클 확인
//  2. BFS : 사이클 -> 도착지점 경로 확인
//
// 시도
//  1. 19% 실패 (사이클 -> 탐색 오류)
//     - 도착 지점이 사이클에 포함된 경우와 포함되지 않은 경우로 확인 
//  2. 51% 실패 (범위 오버로딩)
//     - 예상(int) : ~5*10^7 (50 * 1,000,000)
//                : 간선만 고려 
//     - 실제(long long) : 2.5*10^9 (50 * 50 * 1,000,000)
//                      : 사이클 고려
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const string cycle = "Gee", fail = "gg";

int n, s, e, m, incomes[51];
// 벨만포드 포맷
vector<vector<ll>> edges;

void solution()
{
	vector<bool> isCycle(n);

	vector<ll> totals(n, LLONG_MIN);
	totals[s] = incomes[s];

	// 벨만포드 
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int from = edges[j][0];
			int to = edges[j][1];
			ll cost = edges[j][2];

			// 경로 없음
			if (totals[from] == LLONG_MIN) continue;
			ll income = totals[from] - cost + incomes[to];
			// 이미 최적의 경로를 찾은 경우
			if (totals[to] >= income) continue;

			// 갱신
			totals[to] = income;
			// n번째 시도에서 갱신된 경우 (사이클)
			if (i == n - 1)
				isCycle[to] = true;
		}
	}

	// 도착할 수 없음
	if (totals[e] == LLONG_MIN)
	{
		cout << fail << '\n';
		return;
	}
	// 도착지점이 사이클에 포함된 경우
	if (isCycle[e])
	{
		cout << cycle << '\n';
		return;
	}

	// 사이클 -> 도착지점 확인
	// 그래프 포맷
	vector<vector<int>> graph(n);
	for (auto& e : edges)
		graph[e[0]].push_back(e[1]);

	vector<bool> visited(n, false);
	queue<int> q;
	for (int i = 0; i < n; i++)
	{
		if (isCycle[i] && !visited[i])
		{
			visited[i] = true;
			q.push({ i });
			while (!q.empty())
			{
				int cur = q.front();
				q.pop();
				for (auto& next : graph[cur])
				{
					if (visited[next]) continue;
					if (next == e)
					{
						cout << cycle << '\n';
						return;
					}
					visited[next] = true;
					q.push(next);
				}
			}

		}
	}

	// 사이클이 아닌 경우
	cout << totals[e] << '\n';
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> s >> e >> m;
	edges.assign(m, vector<ll>(3));
	for (int i = 0; i < m; i++)
		cin >> edges[i][0] >> edges[i][1] >> edges[i][2];

	for (int i = 0; i < n; i++)
		cin >> incomes[i];

	solution();
	return 0;
}