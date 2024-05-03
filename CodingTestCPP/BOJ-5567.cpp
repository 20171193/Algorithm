// 백준 5567번 결혼식

// 상근이의 학번 : 1
// depth가 2인 친구까지 탐색

#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<int> vec[10001];
int n, m, answer;

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int s, e;
		cin >> s >> e;
		vec[s].push_back(e);
		vec[e].push_back(s);
	}

	set<int> fr;

	// depth1 친구 반복
	for (int i = 0; i < vec[1].size(); i++)
	{
		fr.insert(vec[1][i]);
		// depth2 친구 반복
		for (int j = 0; j < vec[vec[1][i]].size(); j++)
		{
			fr.insert(vec[vec[1][i]][j]);
		}
	}

	if (fr.empty())
		cout << 0 << '\n';
	else
		// -1 : 상근이 제거
		cout << fr.size() - 1 << '\n';

	return 0;
}