// 백준 2342번 : Dance Dance Revolution
#include <iostream>
#include <vector>
using namespace std;

constexpr int INF = 400004;

// 1. 두 발이 같은 지점에 있으면 안됨.
// 2. 비용
bool isOpposite(int a, int b)
{
	if ((a == 1 && b == 3) || (a == 3 && b == 1)
		|| (a == 2 && b == 4) || (a == 4 && b == 2))
		return true;
	return false;
}

int GetCost(int start, int end)
{
	//  중앙에서 이동 : 2
	if (start == 0) return 2;
	//  현재위치 반복 : 1
	if (start == end) return 1;
	//  반대 지점 : 4
	if (isOpposite(start, end))
		return 4;
	// 인접 지점
	return 3;
}

int solution(const vector<int>& order)
{
	int answer = INF;

	int n = order.size();

	vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(5, vector<int>(5, INF)));
	dp[0][0][0] = 0;

	for (int i = 1; i <= order.size(); i++)
	{
		int next = order[i - 1];
		for (int l = 0; l < 5; l++)
		{
			for (int r = 0; r < 5; r++)
			{
				if (dp[i - 1][l][r] == INF) continue;

				if (next != l)
					dp[i][l][next] = min(dp[i][l][next], dp[i - 1][l][r] + GetCost(r, next));
				if (next != r)
					dp[i][next][r] = min(dp[i][next][r], dp[i - 1][l][r] + GetCost(l, next));
			}
		}
	}

	for (int l = 0; l < 5; l++)
	{
		for (int r = 0; r < 5; r++)
		{
			if (l == r || dp[n][l][r] == INF) continue;
			answer = min(answer, dp[n][l][r]);
		}
	}
	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 0;
	vector<int> orders;

	while (true)
	{
		cin >> n;
		if (n == 0) break;
		orders.push_back(n);
	}

	cout << solution(orders);
	return 0;
}