// 백준 2477번 : 참외밭
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 외적

// 동,서,남,북
// 1, 2, 3, 4
int dx[5] = { 0, 1, -1, 0,0 };
int dy[5] = { 0, 0,0,-1,1 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int k = 0;
	cin >> k;

	int cx = 0, cy = 0;
	vector<pair<int, int>> pos;
	int dir = 0, dist = 0;
	while (cin >> dir >> dist)
	{
		cx += dx[dir] * dist;
		cy += dy[dir] * dist;
		pos.push_back({ cx,cy });
	}

	// 외적
	float area = 0;
	for (int i = 0; i < pos.size(); i++)
	{
		area += pos[i].first * pos[(i + 1) % pos.size()].second
			- pos[i].second * pos[(i + 1) % pos.size()].first;
	}

	cout << ceil(abs(area) / 2.0f) * k << '\n';

	return 0;
}