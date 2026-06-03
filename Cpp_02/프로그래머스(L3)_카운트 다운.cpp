// 프로그래머스(L3) : 카운트 다운
// 조건
// 1. 매 턴마다 다트를 던져 점수를 깎아 0점을 만드는 게임.(음수가 되면 실격)
// 2. 싱글(*1),더블(*2),트리플(*3),불(50)
// 3. 두 선수 동시에 0점을 만든 경우
//  3-1. '싱글' 또는 '불'을 더 많이 던진 선수가 승리
//       그마저도 같다면 선공인 선수가 승리
// 4. 목표 점수가 주어졌을 때
//    {최선의 경우 던질 다트 수, 그 때의 '싱글' 또는 '불'을 맞춘 횟수의 합} 리턴
// 풀이
// 1. DP, 조건식 람다
#include <string>
#include <vector>
#include <numeric>
#include <queue>
using namespace std;

vector<int> solution(int target) {
    vector<int> answer;
    vector<pair<int, int>> dp(target + 1, { target + 1,0 });
    dp[0] = { 0, 0 };

    for (int i = 0; i < target; i++) {
        if (dp[i].first > target) continue;

        // 전이되는 점수, 불/싱글 여부
        auto update = [&](int score, bool isSingle) {
            int nextNum = i + score;
            int nextCnt = dp[i].first + 1;
            int nextSingle = dp[i].second + isSingle;
            if (nextNum > target) return;
            if (dp[nextNum].first > nextCnt ||
                (dp[nextNum].first == nextCnt && dp[nextNum].second < nextSingle)) {
                dp[nextNum] = { nextCnt, nextSingle };
            }
            };

        update(50, 1);  // 불
        for (int s = 1; s <= 20; s++) {
            update(s, 1);   // 싱글
            update(s * 2, 0);
            update(s * 3, 0);
        }
    }


    return answer = { dp[target].first, dp[target].second };
}
