// 백준17182번 : 우주 탐사선(https://www.acmicpc.net/problem/17182)
// 1. 모든 행성을 탐사하는데 걸리는 '최소 시간'
// 2. 중복 방문이 가능
//  - 플로이드-워셜 (각 노드간 최소 비용)
// 3. n <= 10 (비트마스킹 고려)
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int n, k, costs[11][11];

int solution()
{
	// 각 노드간 최소 비용 계산 (플로이드-워셜 n^3)
	vector<vector<int>> mnCosts(n, vector<int>(n));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mnCosts[i][j] = costs[i][j];

	for (int w = 0; w < n; w++)			// 경유지
		for (int s = 0; s < n; s++)		// 시작점
			for (int e = 0; e < n; e++)	// 도착점
				if (mnCosts[s][e] > mnCosts[s][w] + mnCosts[w][e])
					mnCosts[s][e] = mnCosts[s][w] + mnCosts[w][e];

	// 모든 노드를 방문하는 최소비용
	int fullVisited = (1 << n) - 1;
	vector<vector<int>> visitCosts(n, vector<int>(fullVisited + 1, INT_MAX));
	visitCosts[k][1 << k] = 0;
	for (int visited = 1; visited <= fullVisited; visited++)
	{
		for (int cur = 0; cur < n; cur++)
		{
			if (visitCosts[cur][visited] == INT_MAX) continue;

			for (int next = 0; next < n; next++)
			{
				if (visited & (1 << next)) continue;
				int nextVisited = visited | (1 << next);
				visitCosts[next][nextVisited]
					= min(visitCosts[next][nextVisited], visitCosts[cur][visited] + mnCosts[cur][next]);
			}
		}
	}

	int answer = INT_MAX;
	for (int i = 0; i < n; i++)
		answer = min(answer, visitCosts[i][fullVisited]);

	return answer;
}

int main()
{
	cin >> n >> k;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> costs[i][j];

	cout << solution() << '\n';
	return 0;
}