// 백준 1717번 집합의 표현
#include <iostream>
#include <vector>
using namespace std;

int n, m;
// 0 a b : Union(a,b)
// 1 a b : IsLinked(a,b)
int Find(int a, vector<int>& root)
{
	if (root[a] != a)
		root[a] = Find(root[a], root);

	return root[a];
}
void Union(int a, int b, vector<int>& root, vector<int>& depth)
{
	int rootA = Find(a, root);
	int rootB = Find(b, root);

	if (rootA == rootB)
		return;

	if (depth[rootA] < depth[rootB])
		root[rootA] = rootB;
	else if (depth[rootA] > depth[rootB])
		root[rootB] = rootA;
	else
	{
		root[rootB] = rootA;
		depth[rootA]++;
	}
}

bool IsLinked(int a, int b, vector<int>& root)
{
	return Find(a, root) == Find(b, root);
}
int main()
{
	cin >> n >> m;
	vector<int> root(n + 1);
	vector<int> depth(n + 1);
	vector<string> answer;
	for (int i = 1; i <= n; i++)
	{
		root[i] = i;
		depth[i] = 0;
	}

	while (m-- > 0)
	{
		int oper, a, b;
		cin >> oper >> a >> b;

		if (oper == 0)
			Union(a, b, root, depth);
		else
		{
			if (IsLinked(a, b, root))
				answer.push_back("YES");
			else
				answer.push_back("NO");
		}
	}

	for (string a : answer)
		cout << a << '\n';
	return 0;
}