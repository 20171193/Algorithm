// 백준2623번 : 음악프로그램
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;

int main()
{
	cin >> n >> m;
	// 단방향 그래프
	vector<vector<int>> graph(n + 1);

	// 진입차수
	vector<int> degree(n + 1, 0);

	for (int i = 0; i < m; i++)
	{
		int num;
		cin >> num;
		vector<int> vec(num);
		for (int j = 0; j < num; j++)
			cin >> vec[j];

		for (int j = 0; j < num - 1; j++)
		{
			int from = vec[j];
			int to = vec[j + 1];

			graph[from].push_back(to);
			degree[to]++;
		}
	}

	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (degree[i] == 0)
			q.push(i);

	vector<int> result;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		result.push_back(cur);

		// 현 노드 할당 후 차수--
		for (int next : graph[cur])
		{
			degree[next]--;
			if (degree[next] == 0)
				q.push(next);
		}
	}

	if (result.size() != n)
		cout << 0 << '\n';
	else
		for (int res : result)
			cout << res << '\n';

	return 0;
}