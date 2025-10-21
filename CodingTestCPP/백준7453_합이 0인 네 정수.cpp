// 백준 7453번 : 합이 0인 네 정수
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int solution(int n, const vector<vector<int>>& vec)
{
	int answer = 0;

	vector<ll> ab, cd;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ab.push_back(vec[0][i] + vec[1][j]);
			cd.push_back(vec[2][i] + vec[3][j]);
		}
	}

	sort(cd.begin(), cd.end());

	for (ll val : ab)
	{
		auto range = equal_range(cd.begin(), cd.end(), -val);
		answer += distance(range.first, range.second);
	}

	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 0;
	cin >> n;

	vector<vector<int>> vec(4, vector<int>(n));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < 4; j++)
			cin >> vec[j][i];

	cout << solution(n, vec) << '\n';

	return 0;
}