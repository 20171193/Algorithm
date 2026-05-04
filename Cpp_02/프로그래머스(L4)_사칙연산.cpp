// 프로그래머스(L4) : 사칙연산
// 조건
// 1. arr배열(수식)의 서로 다른 연산순서의 계산 결과 중 
//    최댓값을 return
// 2. arr[i](3<=i<=201), 숫자n(2<=n<=101), 연산자o(o=n-1) 
// 풀이
// 1. max_dp[i][j], min_dp[i][j] : i~j의 연산결과
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int solution(vector<string> arr)
{
    int answer = -1;
  
    vector<int> nums;
    vector<char> opers;
    for (int i = 0; i < arr.size(); i++) {
        if (i % 2 == 0) nums.push_back(stoi(arr[i]));
        else opers.push_back(arr[i][0]);
    }

    const int MIN_VALUE = -1000 * 102, MAX_VALUE = 1000 * 102;
    vector<vector<int>> max_dp(nums.size(), vector<int>(nums.size(), MIN_VALUE));
    vector<vector<int>> min_dp(nums.size(), vector<int>(nums.size(), MAX_VALUE));

    for (int i = 0; i < nums.size(); i++) 
        max_dp[i][i] = min_dp[i][i] = nums[i];

    for (int range = 0; range < nums.size(); range++) {
        for (int s = 0; s < nums.size() - range; s++) {
            int e = s + range;

            for (int m = s; m < e; m++) {
                if (opers[m] == '+') {
                    max_dp[s][e] = max(max_dp[s][e], max_dp[s][m] + max_dp[m + 1][e]);
                    min_dp[s][e] = min(min_dp[s][e], min_dp[s][m] + min_dp[m + 1][e]);
                }
                else {
                    // 최대 : 좌항을 최대로
                    max_dp[s][e] = max(max_dp[s][e], max_dp[s][m] - min_dp[m + 1][e]);
                    // 최소 : 우항을 최대로 
                    min_dp[s][e] = min(min_dp[s][e], min_dp[s][m] - max_dp[m + 1][e]);
                }
            }
        }
    }

    return answer = max_dp[0][nums.size()-1];
}