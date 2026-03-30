// 백준 1991번 트리 순회

#include <iostream>
#include <memory.h>
using namespace std;

// A = 65
// 루트는 항상 A
int n;
pair<int, int> nodes[27];
bool visited[27];

// 전위 순회
void Pre(int node)
{
	if (visited[node]) return;

	cout << (char)(node + 'A');
	visited[node];

	if (nodes[node].first != -1)
		Pre(nodes[node].first);
	if (nodes[node].second != -1)
		Pre(nodes[node].second);
}

// 중위 순회
void In(int node)
{
	if (visited[node]) return;

	if (nodes[node].first != -1)
		In(nodes[node].first);

	cout << (char)(node + 'A');
	visited[node];

	if (nodes[node].second != -1)
		In(nodes[node].second);
}

// 후위 순회
void Post(int node)
{
	if (visited[node]) return;

	if (nodes[node].first != -1)
		Post(nodes[node].first);

	if (nodes[node].second != -1)
		Post(nodes[node].second);

	cout << (char)(node + 'A');
	visited[node];
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		char p = 0, lc = 0, rc = 0;
		cin >> p >> lc >> rc;
		nodes[p - 'A'] = make_pair(lc < 'A' ? -1 : lc - 'A', rc < 'A' ? -1 : rc - 'A');
	}

	Pre(0);
	memset(visited, false, sizeof(visited));
	cout << '\n';
	In(0);
	memset(visited, false, sizeof(visited));
	cout << '\n';
	Post(0);

	return 0;
}