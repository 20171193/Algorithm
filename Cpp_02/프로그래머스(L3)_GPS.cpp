// 프로그래머스(L3) : GPS
// 문제
// 1. 수집한 이동 경로의 오류를 최소한으로 수정하여 정확한 이동 경로를 구하고 싶음.
// 2. 거점 간 이동은 도로가 있는 경우에만 가능
// 3. 택시는 한 거점에 머무를 수 있고, 왔던 길을 되돌아갈 수 있음.
// 4. 모든 도로는 왕복도로
// 5. 가능한 경로로 만드는 오류 수정 최소 횟수 출력
// 조건
// 1. 거점 개수 n : 2<=n<=200
// 2. 도로 개수 m : 1<=m<=10,000
// 3. 시간대 별 정보 개수 k : 2<=k<=100
// 풀이
// 1. dp[t][n] : t시간에 n위치를 확정할 때, 오류 수정 횟수의 최솟값
#include <vector>
#include <climits>
using namespace std;

int solution(int n, int m, vector<vector<int>> edge_list, int k, vector<int> gps_log) {
    int answer = 0;

    vector<vector<int>> graph(n + 1);
    // 제자리에 머무는 경우
    for (int i = 1; i <= n; i++) graph[i] = { i };

    for (const auto& e : edge_list) {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    vector<vector<int>> dp(k, vector<int>(n + 1, INT_MAX));
    dp[0][gps_log[0]] = 0;

    for (int time = 1; time < k; time++) {
        for (int from = 1; from <= n; from++) {
            if (dp[time - 1][from] == INT_MAX) continue;
            for (int to : graph[from])
                dp[time][to] = min(dp[time][to], dp[time - 1][from] + (gps_log[time] != to));
        }
    }

    answer = dp[k - 1][gps_log[k - 1]];
    return answer == INT_MAX ? -1 : answer;
}