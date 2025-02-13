// 백준 2098번 - 외판원 순회
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 987654321;
int n, arr[16][16], dp[16][1 << 16];

int solution()
{
	int answer = INF;

	fill(&dp[0][0], &dp[15][1 << 16], INF);

	// 0번을 시작 도시로 
	dp[0][1] = 0;

	// 모든 경로에 대해 탐색
	for (int visited = 0; visited < (1 << n); visited++)
	{
		// 현재 탐색할 도시
		for (int cur = 0; cur < n; cur++)
		{
			// 현재 경로에 cur 도시가 포함되지 않은 경우
			if (!(visited & (1 << cur))) continue;

			// 다음 탐색할 도시
			for (int next = 0; next < n; next++)
			{
				// 현재 경로에 next 도시가 포함되지 않은 경우
				if (visited & (1 << next)) continue;
				if (arr[cur][next] == 0) continue;

				int visitValue = visited | (1 << next);
				dp[next][visitValue] = min(dp[next][visitValue], dp[cur][visited] + arr[cur][next]);
			}
		}
	}

	// 복귀 경로비용 계산
	for (int i = 1; i < n; i++)
	{
		if (arr[i][0] == 0) continue;
		answer = min(answer, dp[i][(1 << n) - 1] + arr[i][0]);
	}
	return answer;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];

	cout << solution() << '\n';

	return 0;
}

