// 프로그래머스(L3) : 110 옮기기
// 조건
// 1. 문자열 s에 있는 "110"을 뽑아서 임의의 위치에 삽입하여
//    사전 순으로 가장 앞에 오는 문자열을 출력
// 풀이
// 1. 우선 순위 0 > 1 : 0을 기준으로 패턴 파악
//  1-1. 패턴 우선 순위(0or10 > 110 > 1)
// 2. 스택 방식 삽입/소거
//  2-1. 1 : 스택 삽입(카운팅)
//  2-2. 0 : 현재 스택 확인 후 스택에서 1제거, 결과 문자열 할당
#include <string>
#include <vector>
using namespace std;

vector<string> solution(vector<string> s) {
    vector<string> answer;

    for (const string& str : s) {
        string result;
        int oneCnt = 0, setCnt = 0;
        for (const char& c : str) {
            if (c == '1') oneCnt++; // '1' 스택 삽입(카운팅)
            else {
                // "110"만족(카운팅)
                if (oneCnt >= 2) {
                    oneCnt -= 2;
                    setCnt++;
                }
                // '0' 혹은 '10'만족(바로 삽입)
                else {
                    if (oneCnt) {
                        oneCnt--;
                        result += '1';
                    }
                    result += '0';
                }
            }
        }

        for (int i = 0; i < setCnt; i++) result += "110";
        for (int i = 0; i < oneCnt; i++) result += '1';
        answer.push_back(result);
    }

    return answer;
}
