// 백준 2342번 : Dance Dance Revolution
// 연속 : 1, 중앙 : 2, 인접 : 3, 반대 4
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 400003;

int arr[1001];
int dp[1001][5][5];

int GetCost(int cur, int next)
{
	// 연속
	if (cur == next) return 1;
	// 중앙
	if (cur == 0) return 2;
	// 반대
	if (abs(next - cur) == 2) return 4;
	// 인접
	else return 3;
}

int solve(int size)
{
	int answer = INF;

	fill(&dp[0][0][0], &dp[0][0][0] + (size + 1) * 5 * 5, INF);
	dp[0][0][0] = 0;

	int next;
	// n-1 반복
	for (int i = 0; i < size; i++)
	{
		next = arr[i];
		for (int l = 0; l < 5; l++)
		{
			for (int r = 0; r < 5; r++)
			{
				if (dp[i][l][r] == INF) continue;

				// 한 지점에 같은 발x
				if (next != r)
					dp[i + 1][next][r] = min(dp[i + 1][next][r], dp[i][l][r] + GetCost(l, next));
				if (next != l)
					dp[i + 1][l][next] = min(dp[i + 1][l][next], dp[i][l][r] + GetCost(r, next));
			}
		}
	}

	// dp[n][][]
	for (int l = 0; l < 5; l++)
		for (int r = 0; r < 5; r++)
			answer = min(answer, dp[size][l][r]);

	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, idx = 0;
	while (cin >> n && n != 0)
		arr[idx++] = n;

	cout << solve(idx) << '\n';

	return 0;
}