// 프로그래머스(L4) : 행렬과 연산
// 문제
// 1. ShiftRow : 모든 행이 아래쪽으로 한 칸씩 밀려남.(i번째 행이 i+1번재 행이 됨)
// 2. Rotate : 행렬의 바깥쪽에 있는 원소들을 시계 방향으로 한 칸 회전
// 3. 모든 행렬 연산 이후 결과 행렬을 출력
// 조건
// 1. 4 <= r*c <= 100,000
// 2. 1 <= operations <= 100,000
// 풀이
// 1. 단순 반복 연산횟수
//  1-1. ShiftRow : r*c (최대 100,000)
//  1-2. Rotate : 2r + 2c
//  1-3. ShiftRow * 100,000 : 10^10 - 불가
// 2. 행렬 -> 덱으로 관리
// 실패
//  1-1. MAX_COL == 2 인 경우 mid_row 존재안함(segmentation fault)
//  1-2. front(), back(), push_front(), push_pop() 오버헤드
// 해결
//  1-1. if(MAX_COL < 2) else 분기 구분 따로 처리
//  1-2. 최초 할당, 정답 할당 시 인덱스 접근,
//       행 복사 시 std::move 전달(강제 참조 캐스팅)
#include <string>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

void Print(const int MAX_ROW, const int MAX_COL, const string& oper, deque<int>& left_col, deque<int>& right_col, deque<deque<int>>& mid_row){
    cout << oper << '\n';
    for (int r = 0; r < MAX_ROW; r++)
    {
        for (int c = 0; c < MAX_COL; c++)
        {
            if (c == 0) cout << left_col[r];
            else if (c == MAX_COL - 1)cout << right_col[r];
            else cout << mid_row[r][c-1];

            cout << ' ';
        }
        cout << '\n';
    }


}

vector<vector<int>> solution(vector<vector<int>> rc, vector<string> operations)
{
    const int MAX_ROW = rc.size();
    const int MAX_COL = rc.front().size();

    vector<vector<int>> answer(MAX_ROW, vector<int>(MAX_COL));

    // 덱 포맷
    deque<int> left_col(MAX_ROW, 0), right_col(MAX_ROW, 0);
    deque<deque<int>> mid_row(MAX_ROW, deque<int>(MAX_COL-2, 0));

    for (int r = 0; r < MAX_ROW; r++)
    {
        for (int c = 0; c < MAX_COL; c++)
        {
            int val = rc[r][c];

            if (c == 0) left_col[r] = val;
            else if (c == MAX_COL - 1) right_col[r] = val;
            else mid_row[r][c-1] = val;
        }
    }

    // 명령 처리
    for(auto& str : operations){
        // ShiftRow
        if(str[0] == 'S'){
            left_col.push_front(left_col.back()); left_col.pop_back();
            right_col.push_front(right_col.back()); right_col.pop_back();
            mid_row.push_front(move(mid_row.back())); mid_row.pop_back();
        }
        // Rotate
        else{
            // 중간 열이 존재하는 경우
            if(MAX_COL > 2){
                // 상단
                right_col.push_front(mid_row.front().back()); mid_row.front().pop_back();
                mid_row.front().push_front(left_col.front()); left_col.pop_front();

                // 하단
                left_col.push_back(mid_row.back().front()); mid_row.back().pop_front();
                mid_row.back().push_back(right_col.back()); right_col.pop_back();
            }
            else{
                // 상단
                right_col.push_front(left_col.front()); left_col.pop_front();

                // 하단
                left_col.push_back(right_col.back()); right_col.pop_back();
            }
        }
    }

    // 정답 할당
    for (int r = 0; r < MAX_ROW; r++)
    {
        for (int c = 0; c < MAX_COL; c++)
        {
            if (c == 0) answer[r][c] = left_col[r];
            else if (c == MAX_COL - 1) answer[r][c] = right_col[r];
            else answer[r][c] = mid_row[r][c-1];
        }
    }

    return answer;
}
