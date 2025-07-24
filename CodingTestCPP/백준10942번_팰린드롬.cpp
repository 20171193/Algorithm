// 백준10942번 : 팰린드롬?
#include <iostream>
#include <vector>
using namespace std;

int n, m;

vector<int> solution(const vector<int>& numbers, const vector<pair<int, int>>& intervals)
{
	vector<int> result(intervals.size());

	int totalLength = numbers.size();
	vector<vector<bool>> isPD(totalLength, vector<bool>(totalLength, false));

	// 길이 1 팰린드롬 (자기자신)
	for (int i = 0; i < totalLength; i++)
		isPD[i][i] = true;
	// 길이 2 팰린드롬
	for (int i = 0; i < totalLength - 1; i++)
		isPD[i][i + 1] = (numbers[i] == numbers[i + 1]);

	// 길이 3이상 팰린드롬
	for (int i = 2; i < totalLength; i++)
	{
		for (int s = 0; s < totalLength - i; s++)
		{
			int e = s + i;
			if (numbers[s] != numbers[e])
				continue;
			if (!isPD[s + 1][e - 1])
				continue;

			isPD[s][e] = true;
		}
	}

	for (int i = 0; i < intervals.size(); i++)
	{
		pair<int, int> itv = intervals[i];
		// 입력은 1based
		result[i] = (int)isPD[itv.first - 1][itv.second - 1];
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// input
	cin >> n;
	vector<int> numbers(n);
	for (int i = 0; i < n; i++)
		cin >> numbers[i];

	cin >> m;
	vector<pair<int, int>> intervals(m);
	for (int i = 0; i < m; i++)
		cin >> intervals[i].first >> intervals[i].second;

	// output
	for (int answer : solution(numbers, intervals))
		cout << answer << '\n';

	return 0;
}