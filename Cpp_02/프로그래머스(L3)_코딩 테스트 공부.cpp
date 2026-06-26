// 프로그래머스(L3) : 코딩 테스트 공부
// 문제
// 1. 특정 문제를 풀기 위해 일정 수치 이상의 {알고력, 코딩력} 필요
// 2. 알고력/코딩력
//  2-1. 각각 1시간 공부를해서 1씩 증가 가능
//  2-2. 문제를 풀어 획득 가능 (문제는 반복해서 풀 수 있음)
// 3. 모든 문제를 풀 수 있는 최단시간을 리턴
// 조건
// 1. 초기 알고력/코딩력 : 0<=alp,cop<=150
// 2. 문제 개수 : 1<=problems.size()<=100
// 3. 문제 {alp_req, cop_req, alp_rwd, cop_rwd, cost} : 0<=req<=150, 0<=rwd<=30, 1<=cost<=10
// 풀이
// 1. dp + 집계범위 클램핑
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(int alp, int cop, vector<vector<int>> problems) {
    const int INF = 10001;
    int answer = 0;

    int maxAlp = 0, maxCop = 0;
    for (const vector<int>& p : problems) {
        maxAlp = max(maxAlp, p[0]);
        maxCop = max(maxCop, p[1]);
    }

    vector<vector<int>> dp(301, vector<int>(301, INF));

    alp = min(alp, maxAlp);
    cop = min(cop, maxCop);
    dp[alp][cop] = 0;
    for (int a = alp; a <= maxAlp; a++) {
        for (int c = cop; c <= maxCop; c++) {
            if (dp[a][c] == INF) continue;

            dp[a + 1][c] = min(dp[a + 1][c], dp[a][c] + 1);
            dp[a][c+1] = min(dp[a][c+1], dp[a][c] + 1);

            for (auto& p : problems) {
                if (a >= p[0] && c >= p[1]) {
                    int na = min(maxAlp, a + p[2]);
                    int nc = min(maxCop, c + p[3]);

                    dp[na][nc] = min(dp[na][nc], dp[a][c] + p[4]);
                }
            }
        }
    }

    answer = dp[maxAlp][maxCop];
    return answer;
}