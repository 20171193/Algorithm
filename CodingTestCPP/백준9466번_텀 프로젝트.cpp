// 백준 9466번 : 텀 프로젝트
// 사이클 root -> .... -> root
#include <iostream>
#include <queue>
#include <memory.h>
#include <vector>
using namespace std;

const int MAX = 100'000;

int t, n, edge[MAX + 1];
bool inGroup[MAX + 1], visited[MAX + 1];
vector<int> answers;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;
	while (t--)
	{
		cin >> n;

		memset(edge, 0, sizeof(int) * (n + 1));
		memset(inGroup, false, sizeof(bool) * (n + 1));
		memset(visited, false, sizeof(bool) * (n + 1));

		for (int i = 1; i <= n; i++)
			cin >> edge[i];

		for (int i = 1; i <= n; i++)
		{
			if (inGroup[i] || visited[i])
				continue;

			queue<int> path;
			int cur = i;
			while (!visited[cur])
			{
				visited[cur] = true;
				path.push(cur);

				cur = edge[cur];
			}

			// 사이클이 아닌 경로제거
			while (!path.empty() && path.front() != cur)
				path.pop();

			while (!path.empty())
			{
				inGroup[path.front()] = true;
				path.pop();
			}
		}

		int count = 0;
		for (int i = 1; i <= n; i++)
			if (!inGroup[i])
				count++;

		answers.push_back(count);
	}

	for (int answer : answers)
		cout << answer << '\n';

	return 0;
}