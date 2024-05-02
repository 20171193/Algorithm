// 백준 1446 지름길

// 운전해야하는 거리의 최솟값
// 일방통행, 역주행 불가능

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, d, dp[10001];
vector<vector<int>> vec;

int main()
{
	cin >> n >> d;

	for (int i = 0; i < n; i++)
	{
		int s, e, t;
		cin >> s >> e >> t;

		// 고속도로의 길이보다 시작점, 도착점이 멀리 있는 경우
		// 지름길을 고려할 필요가 없는 경우 미리 제외
		if (s > d || e > d || e - s < t) continue;

		vector<int> temp;

		temp.push_back(s);
		temp.push_back(e);
		temp.push_back(t);

		vec.push_back(temp);
	}

	sort(vec.begin(), vec.end());
	for (int i = 1; i <= d; i++)
	{
		// 현재 위치까지 거리 갱신
		dp[i] = dp[i - 1] + 1;
		for (int j = 0; j < vec.size(); j++)
		{
			// 지름길의 도착지점 중 현재위치가 있는 경우
			if (vec[j][1] == i)
				dp[i] = min(dp[i], dp[vec[j][0]] + vec[j][2]);
		}
	}

	cout << dp[d] << '\n';

	return 0;
}