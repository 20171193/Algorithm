// 백준 2618번 : 경찰차
// N <= 1000, M <= 1000
#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>
using namespace std;

int n, m, result, accDist[1001][1001], carNumber[1001][1001];
pair<int, int> inc[1001];

int GetManhattan(const pair<int, int>& origin, const pair<int, int>& destination)
{
	return abs(destination.first - origin.first) + abs(destination.second - origin.second);
}

int req(int inc1, int inc2)
{
	int nextInc = max(inc1, inc2) + 1;
	if (nextInc > m)
		return 0;

	int curDist = accDist[inc1][inc2];
	if (curDist != -1)
		return curDist;

	pair<int, int> target = inc[nextInc - 1];
	pair<int, int> car1 = inc1 == 0 ? make_pair(1, 1) : inc[inc1 - 1];
	pair<int, int> car2 = inc2 == 0 ? make_pair(n, n) : inc[inc2 - 1];

	int dist1 = GetManhattan(car1, target) + req(nextInc, inc2);	// 1번 이동
	int dist2 = GetManhattan(car2, target) + req(inc1, nextInc);	// 2번 이동

	if (dist1 < dist2)
	{
		carNumber[inc1][inc2] = 1;
		return accDist[inc1][inc2] = dist1;
	}
	else
	{
		carNumber[inc1][inc2] = 2;
		return accDist[inc1][inc2] = dist2;
	}
}

vector<int> solution()
{
	vector<int> path;

	for (int i = 0; i < m; i++)
		memset(accDist[i], -1, sizeof(int) * m);

	// 메모이제이션 재귀
	result = req(0, 0);

	// 경로 추적
	int inc1 = 0, inc2 = 0;
	for (int i = 0; i < m; i++)
	{
		int num = carNumber[inc1][inc2];
		path.push_back(num);
		num == 1 ? inc1 = i + 1 : inc2 = i + 1;
	}
	return path;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input
	cin >> n >> m;
	for (int i = 0; i < m; i++)
		cin >> inc[i].first >> inc[i].second;

	// output
	vector<int> answer = solution();
	cout << result << '\n';
	for (int ans : answer)
		cout << ans << '\n';
	return 0;
}