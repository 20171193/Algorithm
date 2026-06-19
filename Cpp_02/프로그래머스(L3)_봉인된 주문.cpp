// 프로그래머스(L3) : 봉인된 주문
// 문제
// 1. 특정 주문들을 지웠을 때, n번째 주문을 출력
// 조건
// 1. 주문
//  1-1. 주문은 알파벳 소문자 11글자 이하로 쓸 수 있는 모든 문자열
//  1-2. 글자 수가 적은 주문부터 기록, 사전 순서대로 기록
// 풀이
// 1. 26진수(숫자 -> 문자), (문자 -> 숫자)
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

long long strToNum(const string& str) {
    long long ret = 0;

    int digit = 0;
    for (auto iter = str.rbegin(); iter != str.rend(); iter++, digit++)
        ret += (long long)((*iter) - 'a' + 1) * pow(26, digit);
    return ret;
}

string numToStr(long long num) {
    string ret = "";
    while (num > 0) {
        num--;
        ret += (char)('a' + num % 26);
        num /= 26;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

string solution(long long n, vector<string> bans) {
    string answer = "";

    sort(bans.begin(), bans.end(), [](const string& a, const string& b) {
        if (a.size() != b.size())
            return a.size() < b.size();
        return a < b;
        });

    for (int i = 0; i < bans.size(); i++) {
        long long order = strToNum(bans[i]);

        if (order > n + i) {
            answer = numToStr(n + i);
            break;
        }
    }

    if (answer.size() == 0)
        answer = numToStr(n + bans.size());

    return answer;
}
