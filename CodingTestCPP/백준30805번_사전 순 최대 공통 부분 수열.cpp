// 백준 30805번 : 사전 순 최대 공통 부분 수열
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;

bool comp(const pair<int, int>& a, const pair<int, int>& b)
{
	if (a.first == b.first)
		return a.second < b.second;
	return a.first > b.first;
}

int FindIndex(const vector<int>& view, int start, int size, int num)
{
	if (start < 0 || start >= view.size()) return -1;
	if (size <= 0 || size > view.size()) return -1;

	for (int i = start; i < size; i++)
	{
		if (view[i] == num)
			return i;
	}
	return -1;
}

vector<int> solve(const vector<int>& vecA, const vector<int>& vecB)
{
	vector<int> result;

	// num, index
	vector<pair<int, int>> sorted;
	for (int i = 0; i < vecA.size(); i++)
		sorted.push_back({ vecA[i], i });

	sort(sorted.begin(), sorted.end(), comp);

	int prevIndexA = -1, prevIndexB = -1;
	for (int i = 0; i < sorted.size(); i++)
	{
		int numA = sorted[i].first;
		int indexA = sorted[i].second;

		if (indexA < prevIndexA)
			continue;

		int indexB = FindIndex(vecB, prevIndexB + 1, vecB.size(), numA);
		if (indexB == -1)
			continue;

		prevIndexA = indexA;
		prevIndexB = indexB;
		result.push_back(numA);
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
	vector<int> vecA(n);
	for (int i = 0; i < n; i++)
		cin >> vecA[i];

	cin >> m;
	vector<int> vecB(m);
	for (int i = 0; i < m; i++)
		cin >> vecB[i];


	// output
	vector<int> answer = solve(vecA, vecB);

	cout << answer.size() << '\n';
	for (int num : answer)
		cout << num << ' ';

	return 0;
}