// 프로그래머스(L3) : 보행자 천국
// 입력
// 1. city_map : m*n 격자 배열(1 <= m, n <= 500)
// 조건
// 1. 칸
//  1-1. 0 : 자동차 통행 가능
//  1-2. 1 : 자동차 통행 금지
//  1-3. 2 : 좌회전/우회전 금지 진행방향대로 진행
// 2. 출발지 -> 목적지까지 가능한 경로 수를 MOD로 나누어 출력
// 풀이
// 1. DP[i][j][2] : {i,j}에 수직(0), 수평(1)으로 방문하는 경우의 수
//  => 갱신 시 칸 상태에 따라 수직 or 수평 or 수직/수평 갱신
#include <vector>
using namespace std;

int MOD = 20170805;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(2, 0)));
    dp[0][0] = { 0,1 };

    for (int y = 0; y < m; y++) {
        for (int x = 0; x < n; x++) {
            if (city_map[y][x] == 1) continue;

            // 수직(0), 수평(1)
            for (int d = 0; d < 2; d++) {
                int py = y - (d == 0);
                int px = x - (d == 1);
                if (py < 0 || px < 0) continue;

                if (city_map[py][px] == 2)
                    dp[y][x][d] = (dp[y][x][d] + dp[py][px][d]) % MOD;
                else
                    dp[y][x][d] = (dp[y][x][d] + (dp[py][px][0] + dp[py][px][1]) % MOD) % MOD;
            }
        }
    }

    answer = (dp[m - 1][n - 1][0] + dp[m - 1][n - 1][1]) % MOD;
    return answer;
}
