// 백준 21276번 : 계보 복원가 호석
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

int n, m;
unordered_map<int, string> indexKeyMap;
unordered_map<string, int> nameKeyMap;

bool strcomp(int a, int b)
{
	return indexKeyMap[a] < indexKeyMap[b];
}

int main()
{
	cin >> n;
	vector<string> nameVec(n);
	for (int i = 0; i < n; i++)
		cin >> nameVec[i];

	sort(nameVec.begin(), nameVec.end());
	for (int i = 0; i < nameVec.size(); i++)
	{
		indexKeyMap.insert({ i, nameVec[i] });
		nameKeyMap.insert({ nameVec[i], i });
	}

	vector<vector<int>> edges(n);
	vector<int> degree(n, 0);

	cin >> m;
	for (int i = 0; i < m; i++)
	{
		string child, parent;
		cin >> child >> parent;
		int ci = nameKeyMap[child];
		int pi = nameKeyMap[parent];

		edges[pi].push_back(ci);
		degree[ci]++;
	}

	// 시조 할당(루트)
	vector<int> roots;
	for (int i = 0; i < n; i++)
		if (degree[i] == 0)
			roots.push_back(i);

	cout << roots.size() << '\n';
	for (int i : roots)
		cout << indexKeyMap[i] << ' ';
	cout << '\n';

	for (int i = 0; i < edges.size(); i++)
	{
		cout << indexKeyMap[i] << ' ';

		sort(edges[i].begin(), edges[i].end(), strcomp);

		int pd = degree[i];	// 부모 차수
		int count = 0;
		string childs = "";
		for (int c : edges[i])
		{
			// 1촌만 해당
			if (degree[c] != pd + 1)
				continue;

			count++;
			childs += ' ' + indexKeyMap[c];
		}
		cout << to_string(count) + childs << '\n';
	}

	return 0;
}