// 백준 1099번 : 알 수 없는 문장
// 조건
// 1. 입력으로 주어진 문장을
//    단어들을 변환해 만드는 최소 비용
// 2. 단어 변환 비용
//  - ABC -> ABC = 0
//        -> ACB = 2
//        -> BCA = 3
// 3. 단어 개수/길이 <= 50
//     
// 풀이
// 1. 단어 변환 비용 -> 자리가 바뀌는 단어 개수
// 2. 단어 변환 구현
// 3. dp : i번 인덱스까지 사용한 최소 비용
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int INF = 987654321; 

string context, words[51], sortedWords[51];
int n;

// 요소 확인
bool CanConvert(string target, string sortedWord){
    sort(target.begin(), target.end());
    return target == sortedWord;
}
// 변환 비용
int GetConvertCost(string& target, string& word){
    int cost = 0;
    for(int i =0; i<(int)target.size(); i++)
        cost += target[i] != word[i];
    return cost;
}

int solution(){
    // 단어 비교용
    for (int i = 0; i < n; i++) {
        sortedWords[i] = words[i];
        sort(sortedWords[i].begin(), sortedWords[i].end());
    }

    int targetLength = context.size();

    vector<int> dp(targetLength + 1, INF);
    dp[0] = 0;
    for(int i = 0; i<targetLength; i++){
        if(dp[i] == INF) continue;

        for(int j = 0; j<n; j++){
            int wordLength = words[j].size();
            if(i + wordLength > targetLength) continue;

            string subCtx = context.substr(i, wordLength);
            if(!CanConvert(subCtx, sortedWords[j])) continue;

            int cost = GetConvertCost(subCtx, words[j]);
            dp[i + wordLength] = min(dp[i + wordLength], dp[i] + cost);
        }
    }

    if(dp[targetLength] != INF)
        return dp[targetLength];
    return -1;
}

int main(){
    cin >> context >> n;
    for(int i = 0; i<n; i++)
        cin >> words[i];

    cout << solution() << '\n';
    return 0;
}
