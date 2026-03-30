//백준 15661번 - 링크와 스타트
#include <iostream>
#include <vector>
#include <bit>
#include <algorithm>
using namespace std;

int n, ret = 987654321, arr[21][21];
int CalcAblity(const vector<int>& t)
{
	int abil = 0;

	for (int i = 0; i < t.size() - 1; i++)
		for (int j = i + 1; j < t.size(); j++)
			abil += arr[t[i]][t[j]] + arr[t[j]][t[i]];

	return abil;
}

int GetDiff(const vector<int>& t1, const vector<int>& t2)
{
	return abs(CalcAblity(t1) - CalcAblity(t2));
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];

	for (int i = 1; i < (1 << n); i++)
	{
		vector<int> t1, t2;
		for (int j = 0; j < n; j++)
		{
			if (i & (1 << j))
				t1.push_back(j);
			else
				t2.push_back(j);
		}

		if (!t1.size() || !t2.size())
			continue;

		ret = min(ret, GetDiff(t1, t2));
	}

	cout << ret << '\n';
	return 0;
}