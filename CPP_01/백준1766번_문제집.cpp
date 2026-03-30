// 백준 1766번 : 문제집
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int n, m;

int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(NULL);

	cin >> n >> m;
	string answer = "";
	vector<int> degree(n + 1, 0);
	vector<vector<int>> edges(n + 1);

	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		edges[a].push_back(b);
		degree[b]++;
	}

	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 1; i <= n; i++)
	{
		if (degree[i] == 0)
			pq.push(i);
	}

	while (!pq.empty())
	{
		int cur = pq.top();
		pq.pop();

		cout << cur << ' ';

		for (int next : edges[cur])
		{
			degree[next]--;
			if (degree[next] == 0)
				pq.push(next);
		}
	}

	return 0;
}