// ���� 2668�� ���ڰ���

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
		// ����Ŭ �߰� �� 
		if (dfs(next))
			return true;
	}
	// ���� ��ο� ���� ����� ��� (����Ŭ)
	else if (path[next])
	{
		// ����Ŭ �߰� �� �Ųٷ� Ž��
		int cur = next;
		do {
			cycles.insert(cur);
			cur = arr[cur];
		} while (cur != next);

		return true;
	}

	// ����Ŭ �ƴ�
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