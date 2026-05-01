// 프로그래머스(L3) : N으로 표현
// 조건
// 1. number를 숫자 N과 사칙연산만 사용해서 표현 할 수 있는 방법 중
//    N사용횟수의 최솟값을 return
// 2. N(1<=N<=9), number(1<=number<=32,000)
// 3. 최솟값이 8보다 크면 -1을 return
// 
// 풀이
// 1. dp[i][] : N을 사용하여 만들 수 있는 값의 집합 (uset)
//    최대 5^8 : 사칙연산(+,-,*,/) + nn(n*10+n)
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

typedef long long ll;

int solution(int N, int number) {
    vector<unordered_set<int>> dp(9);
    // 8번 반복
    for (int i = 1; i <= 8; i++) {
        // 이어붙인 수
        string attachStr(i, N + '0');
        int attachNum = stoi(attachStr);
        if (attachNum == number) 
            return i;

        dp[i].insert(attachNum);    

        for (int j = 1; j < i; j++) {
            for (int a : dp[j]) {
                for (int b : dp[i - j]) {
                    // 사칙연산
                    vector<int> nexts = { a + b, a - b, a * b };
                    if (b != 0) nexts.push_back(a / b);

                    for (int next : nexts)
                    {
                        if (next == number) 
                            return i;

                        dp[i].insert(next);
                    }
                }
            }
        }
    }

    return -1;
}