#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

int solution(vector<int> sticker)
{
    int answer = 0;

    vector<int> dp(sticker.size());
    for (int i = 0; i < 2; i++)
    {
        // 원형 리스트
        // i == 0 : 첫번째 요소 고려
        // i == 1 : 마지막 요소 고려

        if (sticker.size() <= i)
            continue;

        int sum = 0;
        dp[i] = sticker[i];
        sum = dp[i];

        for (int j = i + 1; j < sticker.size() - (i == 0 ? 1 : 0); j++)
        {
            dp[j] = max(dp[j - 1], (j - 2 >= i ? dp[j - 2] + sticker[j] : sticker[j]));
            sum = dp[j];
        }
        answer = max(answer, sum);
        fill(dp.begin(), dp.end(), 0);
    }
    return answer;
}