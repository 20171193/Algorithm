// 프로그래머스 L3 : 표 편집
// 조건
// 1. 옵션
//  1-1. U X : X칸 위의 행
//  1-2. D X : X칸 아래 행
//  1-3. C : 현재 행 삭제 후, 아래 행 선택
//         : 마지막 행인 경우 바로 윗 행 선택
//  1-4. Z : 가장 최근에 삭제된 행 복구
//
// 풀이
// 1. 양 방향 연결리스트 구현
//  1-1. 이동 O(N(이동거리)), 삭제/삽입 O(1) 
// 2. 삭제 옵션 스태킹
//  2-1. LIFO
#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

constexpr int PREV = 0, NEXT = 1, IS_ALIVE = 2;

void MoveOper(vector<vector<int>>& linked, const string& str, int& cursor) {
    int totalDist = stoi(str.substr(2));
    for (int d = 0; d < totalDist; d++)
        cursor = (str[0] == 'U') ? linked[cursor][PREV] : linked[cursor][NEXT];
}

void EraseOper(vector<vector<int>>& linked, stack<int>& erasedIndex, int& cursor) {
    erasedIndex.push(cursor);
    linked[cursor][IS_ALIVE] = 0;

    int prev = linked[cursor][PREV];
    int next = linked[cursor][NEXT];

    if (prev >= 0) linked[prev][NEXT] = next;
    if (next < linked.size()) linked[next][PREV] = prev;

    cursor = next < linked.size() ? next : prev;
}

void RestoreOper(vector<vector<int>>& linked, stack<int>& erasedIndex) {
    int idx = erasedIndex.top();
    erasedIndex.pop();
    linked[idx][IS_ALIVE] = 1;

    int prev = linked[idx][PREV];
    int next = linked[idx][NEXT];

    if (prev >= 0) linked[prev][NEXT] = idx;
    if (next < linked.size()) linked[next][PREV] = idx;
}

string solution(int n, int k, vector<string> cmd) {
    string answer = "";

    int cursor = k;

    // {prevIdx, nextIdx, isAlive}
    vector<vector<int>> linked(n);
    for (int i = 0; i < n; i++)
        linked[i] = { i - 1 , i + 1, 1 };

    stack<int> erasedIndex;

    for (const string& str : cmd) {
        char oper = str[0];
        if (oper == 'U' || oper == 'D')
            MoveOper(linked, str, cursor);
        else if (oper == 'C')
            EraseOper(linked, erasedIndex, cursor);
        else  // oper == 'Z'
            RestoreOper(linked, erasedIndex);
    }

    for (int i = 0; i < n; i++)
        answer += linked[i][IS_ALIVE] ? 'O' : 'X';

    return answer;
}

int main() {
    solution(8, 2, { "D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z" });
    return 0;
}