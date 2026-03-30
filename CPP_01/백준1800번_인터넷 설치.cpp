// 백준 1800번 : 인터넷 설치
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef long long ll;

int n, p, k;
vector<vector<pair<int, int>>> edges;

bool Check(int cost)
{
	// node, k
	queue<pair<int, int>> q;
	vector<int> visited(n + 1, k + 1);
	visited[1] = 0;
	q.push({ 1, 0 });

	while (!q.empty())
	{
		int curNode = q.front().first;
		int curK = q.front().second;
		q.pop();

		for (auto& p : edges[curNode])
		{
			int nextNode = p.first;
			int nextCost = p.second;
			if (nextCost > cost)
			{
				if (curK >= k) continue;
				if (visited[nextNode] <= curK + 1) continue;

				visited[nextNode] = curK + 1;
				q.push({ nextNode, curK + 1 });
			}
			else
			{
				if (visited[nextNode] <= curK) continue;

				visited[nextNode] = curK;
				q.push({ nextNode, curK });
			}
		}
	}

	return visited[n] <= k;
}

int solution()
{
	// 비용 기준 이분탐색
	int mn = 0, mx = 1000000;
	while (mn <= mx)
	{
		int mid = (mn + mx) >> 1;

		if (Check(mid))
			mx = mid - 1;
		else
			mn = mid + 1;
	}

	int answer = mn > 1000000 ? -1 : mn;
	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> p >> k;
	edges.assign(n + 1, vector<pair<int, int>>());
	for (int i = 0; i < p; i++)
	{
		int s, e, c;
		cin >> s >> e >> c;
		edges[s].push_back({ e,c });
		edges[e].push_back({ s,c });
	}

	cout << solution() << '\n';
	return 0;
}