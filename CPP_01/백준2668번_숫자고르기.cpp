// 백준 2668번 숫자고르기

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <memory.h>
using namespace std;

int n, ret, arr[101];
bool visited[101], path[101];
set<int> cycles;

bool dfs(int c)
{
	visited[c] = true;
	path[c] = true;

	int next = arr[c];

	if (!visited[next])
	{
		// 사이클 발견 시 
		if (dfs(next))
			return true;
	}
	// 현재 경로에 속한 노드일 경우 (사이클)
	else if (path[next])
	{
		// 사이클 발견 시 거꾸로 탐색
		int cur = next;
		do {
			cycles.insert(cur);
			cur = arr[cur];
		} while (cur != next);

		return true;
	}

	// 사이클 아님
	path[c] = false;
	return false;
}

int main()
{
	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	for (int i = 1; i <= n; i++)
	{
		if (visited[i])
			continue;

		dfs(i);
		memset(visited, 0, sizeof(bool) * (n + 1));
		memset(path, 0, sizeof(bool) * (n + 1));
	}

	cout << cycles.size() << '\n';
	for (int i = 1; i <= n; i++)
		if (cycles.find(i) != cycles.end())
			cout << i << '\n';

	return 0;
}