// 백준 2565번 : 전깃줄
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<pair<int, int>> wires;

int solution()
{
	// LIS
	sort(wires.begin(), wires.end());

	vector<int> lis;
	for (auto& w : wires)
	{
		int to = w.second;
		int index = lower_bound(lis.begin(), lis.end(), to) - lis.begin();

		if (lis.empty() || index == lis.size())
			lis.push_back(to);
		else
			lis[index] = to;
	}

	return wires.size() - lis.size();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	wires.assign(n + 1, { 0,0 });
	for (int i = 0; i < n; i++)
		cin >> wires[i].first >> wires[i].second;

	cout << solution() << '\n';
	return 0;
}