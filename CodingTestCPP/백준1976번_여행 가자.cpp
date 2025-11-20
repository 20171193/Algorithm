// 백준 1976번 : 여행 가자(https://www.acmicpc.net/problem/1976)
// 1. 중복 방문이 가능
//  즉, 방문할 수 있는지만 체크 -> BFS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int n, m, edge[201][201], plan[1001];

string solution()
{
	vector<bool> visited(n + 1);
	queue<int> q;
	q.push(plan[0]);
	visited[plan[0]] = true;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		for (int i = 1; i <= n; i++)
		{
			if (i == cur || !edge[cur][i] || visited[i]) continue;
			q.push(i);
			visited[i] = true;
		}
	}

	for (int i = 0; i < m; i++)
		if (!visited[plan[i]])
			return "NO";
	return "YES";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> edge[i][j];

	for (int i = 0; i < m; i++)
		cin >> plan[i];

	cout << solution() << '\n';
	return 0;
}