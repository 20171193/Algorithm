// 백준 1006번 : 습격자 초라기
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 20002;
int t, n, w, top[10001], bottom[10001];

int min(int i, int d, const vector<vector<int>>& dp)
{
	// 0 : 따로 배치
	if (d == 0)
		return 2 + (*min_element(dp[i - 1].begin(), dp[i - 1].end()));
	// 1 : 위 아래 함께 배치
	if (d == 1 && top[i] + bottom[i] <= w)
		return 1 + (*min_element(dp[i - 1].begin(), dp[i - 1].end()));
	// 2 : 이전 칸과 함께 배치 (아래)
	if (d == 2 && i > 1 && bottom[i - 1] + bottom[i] <= w)
		return 1 + min(dp[i - 1][3], dp[i - 1][0]);
	// 3 : 이전 칸과 함께 배치 (위)
	if (d == 3 && i > 1 && top[i - 1] + top[i] <= w)
		return 1 + min(dp[i - 1][2], dp[i - 1][0]);
	// 4 : 이전 칸과 함께 배치 (위/아래)
	if (d == 4 && i > 1 && top[i - 1] + top[i] <= w && bottom[i - 1] + bottom[i] <= w)
		return dp[i - 1][0];

	return INF;
}

// circleLinkedNumber : 1번째-n번째가 연결되었다고 고려할 경우(2,3,4)
int Memoization(int circleLinkedNumber, vector<vector<int>>& dp)
{
	int start = circleLinkedNumber == 0 ? 1 : 2;
	int end = circleLinkedNumber == 0 ? n : n - 1;

	for (int cur = start; cur <= end; cur++)
		for (int d = 0; d < 5; d++)
			dp[cur][d] = min(cur, d, dp);

	if (circleLinkedNumber == 0)
		return *min_element(dp[n].begin(), dp[n].end());
	else if (circleLinkedNumber == 2  // (1번째 아래 - n번째 아래)
		&& top[n] + top[n - 1] <= w)
		return min({ dp[end][0], dp[end][2] }) - 1;
	else if (circleLinkedNumber == 3  // (1번쨰 위 - n번째 위)
		&& bottom[n] + bottom[n - 1] <= w)
		return min({ dp[end][0], dp[end][3] }) - 1;
	else // circleLinkedNumber == 4		
		return *min_element(dp[end].begin(), dp[end].end());
}

int solution()
{
	int answer = INF;
	vector<vector<int>> dp(n + 1, vector<int>(5, INF));

	// 끝 연결 x
	dp[0][0] = 0;
	answer = min(answer, Memoization(0, dp));

	if (n == 1) return answer;

	// 아래만 연결
	if (bottom[1] + bottom[n] <= w)
	{
		dp.assign(n + 1, vector<int>(5, INF));
		dp[1][2] = 3;
		answer = min(answer, Memoization(2, dp));
	}

	// 위만 연결
	if (top[1] + top[n] <= w)
	{
		dp.assign(n + 1, vector<int>(5, INF));
		dp[1][3] = 3;
		answer = min(answer, Memoization(3, dp));
	}

	// 아래 위 모두 연결
	if (top[1] + top[n] <= w && bottom[1] + bottom[n] <= w)
	{
		dp.assign(n + 1, vector<int>(5, INF));
		dp[1][2] = dp[1][3] = 3;
		dp[1][4] = 2;
		answer = min(answer, Memoization(4, dp));
	}

	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	vector<int> answer;

	cin >> t;
	while (t--)
	{
		cin >> n >> w;
		for (int i = 1; i <= n; i++)
			cin >> bottom[i];
		for (int i = 1; i <= n; i++)
			cin >> top[i];

		answer.push_back(solution());
	}

	for (int ans : answer)
		cout << ans << '\n';

	return 0;
}