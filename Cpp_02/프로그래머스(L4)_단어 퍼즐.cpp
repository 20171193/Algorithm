// 프로그래머스(L4) : 단어 퍼즐
// 풀이
// 1. dp[i] : i글자까지 만드는 최소 단어 개수
//  1-1. 풀이 근거 : strs 내 단어 길이는 최대 5개
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int solution(vector<string> strs, string t) {
    const int INF = 20001;
    int n = t.size();
    
	// 문자열 검색
    unordered_set<string> dict(strs.begin(), strs.end());
    
    vector<int> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int len = 1; len <= 5; len++) {
            if (i - len < 0) break; 
            if (dp[i - len] == INF) continue;
 			
            string sub = t.substr(i - len, len);
            if (dict.find(sub) != dict.end()) 
                dp[i] = min(dp[i], dp[i - len] + 1);
        }
    }

    return dp[n] == INF ? -1 : dp[n];
}