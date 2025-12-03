// 백준 1854번 : K번째 최단경로 찾기(https://www.acmicpc.net/problem/1854)
// 1. 다익스트라로 k개까지의 최소비용 구하기
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

constexpr int INF = 1000001;

vector<int> solution(int n, int k, vector<vector<pair<int, int>>>& edges)
{
	vector<int> result;
	// 비용 최대 힙 (k개에서 갱신)
	vector<priority_queue<int>> costs(n + 1, priority_queue<int>());
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, 1 });
	costs[1].push(0);

	while (!pq.empty())
	{
		int curCost = pq.top().first;
		int curNode = pq.top().second;
		pq.pop();

		for (auto& next : edges[curNode])
		{
			int nextCost = curCost + next.first;
			int nextNode = next.second;

			if (costs[nextNode].size() == k)
			{
				if (costs[nextNode].top() > nextCost)
				{
					costs[nextNode].pop();
					costs[nextNode].push(nextCost);
					pq.push({ nextCost, nextNode });
				}
			}
			else
			{
				costs[nextNode].push(nextCost);
				pq.push({ nextCost, nextNode });
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (costs[i].size() < k)
			result.push_back(-1);
		else
			result.push_back(costs[i].top());
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<int, int>>> edges(n + 1);

	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		edges[a].push_back({ c,b });
	}

	for (int ans : solution(n, k, edges))
		cout << ans << '\n';
	return 0;
}