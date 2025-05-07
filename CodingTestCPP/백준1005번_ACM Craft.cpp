// 백준 1005번 : ACM Craft
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int t, n, k, w;
vector<int> delays, inDegrees, dp, answers;
vector<vector<int>> edges;
queue<int> q;

// 특정 건물을 짓는데 소요되는 최대 시간

int main()
{
	// input
	cin >> t;
	while (t--)
	{
		cin >> n >> k;

		delays.assign(n + 1, 0);
		inDegrees.assign(n + 1, 0);
		dp.assign(n + 1, 0);
		for (int i = 1; i <= n; i++)
			cin >> delays[i];

		edges.assign(n + 1, {});
		for (int i = 0; i < k; i++)
		{
			int s, e;
			cin >> s >> e;
			inDegrees[e]++;
			edges[s].push_back(e);
		}

		cin >> w;

		// solve
		for (int i = 1; i <= n; i++)
		{
			if (inDegrees[i] == 0)
			{
				q.push(i);
				dp[i] = delays[i];
			}
		}

		while (!q.empty())
		{
			int cur = q.front();
			q.pop();

			for (int next : edges[cur])
			{
				dp[next] = max(dp[next], dp[cur] + delays[next]);
				if (--inDegrees[next] == 0)
					q.push(next);
			}
		}

		answers.push_back(dp[w]);
	}

	// output
	for (int ans : answers)
		cout << ans << '\n';

	return 0;
}