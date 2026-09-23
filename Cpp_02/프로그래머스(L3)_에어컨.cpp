// 프로그래머스(L3) : 에어컨
// 문제
// 1. 실내온도를 t1~t2를 유지해야 함.
// 2. 에어컨이 켜져있는 경우
//  2-1. 희망온도 == 실내온도 : 실내온도가 변하지 않음.
//  2-2. 희망온도 != 실내온도 : 매 분 같아지는 방향으로 1도 상승/하강
// 3. 에어컨이 꺼져있는 경우
//  3-1. 실외온도 == 실내온도 : ""
//  3-2. 실외온도 != 실내온도 : ""
// 4. 소비전력
//  4-1. 희망온도 != 실내온도 : 매 분 전력a만큼 소비
//  4-2. 희망온도 == 실내온도 : 매 분 전력b만큼 소비
//  4-3. 에어컨이 꺼져있으면 소비하지 않음.
// 5. 차 내에 승객이 탑승 중일 때 실내온도를 t1~t2도 사이로 유지하면서,
//    소비 전력을 최소로 하는 최소 소비전력을 return.
// 조건
// 1. 실외온도 temperature : -10<=temperature<=40
// 2. 목표온도 t1, t2 : -10<=t1,t2<=40
// 3. 소비전력 다를 때a, 같을 때b : 1<=a,b<=100
// 4. 승객 탑승 정보 onboard : 2<=onboard.size()<=1000
// 5. 불가능한 경우는 주어지지 않음.
// 
// 풀이
// 1. 구간 처리 선택지
//  1-1. on + 조정 : a
//  1-2. on + 유지 : b
//  1-3. off : 0
// 2. dp[i][t] : i분, t도일 때 최소 비용
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    const int SCALE_TEMP = 10;

    int answer = INT_MAX;

    int n = onboard.size();
    int outT = temperature + SCALE_TEMP;
    int lo = t1 + SCALE_TEMP, hi = t2 + SCALE_TEMP;
    vector<vector<int>> dp(n, vector<int>(51, INT_MAX));
    dp[0][outT] = 0;

    bool increase = temperature < t1;
    for (int i = 1; i < n; i++) {
        for (int t = 0; t <= 50; t++) {
            if (dp[i - 1][t] == INT_MAX) continue;
            int prevCost = dp[i - 1][t];

            // on, 조정 (실외 반대 방향)
            int adj = increase ? t + 1 : t - 1;
            if (0 <= adj && adj <= 50)
                dp[i][adj] = min(dp[i][adj], prevCost + a);

            // on, 유지
            dp[i][t] = min(dp[i][t], prevCost + b);

            // off (실외 방향)
            int off = t + (t < outT) - (t > outT);
            dp[i][off] = min(dp[i][off], prevCost);
        }

        // 범위 밖 상태
        if (onboard[i])
            for (int t = 0; t <= 50; t++)
                if (t < lo || t > hi) dp[i][t] = INT_MAX;
    }

    for (int t = 0; t <= 50; t++)
        answer = min(answer, dp[n - 1][t]);

    return answer;
}