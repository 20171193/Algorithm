// 프로그래머스(L3) : 고고학 최고의 발견
// 문제
// 1. 보드의 모든 수가 0이 되게 변경해야 함.
// 2. 한 칸을 회전(순방향)시키면 인접한 칸 모두 회전.
// 3. 최소 회전 횟수 return
// 조건
// 1. 보드 크기 n*n : 2<=n<=8
// 2. 해결 가능한 퍼즐만 주어짐.
// 풀이
// 1. 완탐 : 4^64 불가
// 2. 0번째 행 상태 4^n확정 후 그리디
//  2-0. i행 확정 시 i+1은 정해짐.
//  2-1. 상태 확정 : 완탐(방향(4)^행길이(n) : 4^n)
//  2-2. 그리디 : 윗 행을 조건에 맞게 돌리는 경우만 확정
// 
// 피드백
// 1. cnt >= answer 가지치기 추가
// 2. vector 복사 -> 고정 배열 memcpy
#include <string>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

// 제자리/좌/우/하
int dc[4] = {0,-1,1,0};
int dr[4] = {0,0,0,1};

int origin[8][8], board[8][8];

int solution(vector<vector<int>> clockHands) {
    int n = clockHands.size();  // 행/열 크기
    const int INF = n * n * 4 + 1;
    int answer = INF;

    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            origin[r][c] = clockHands[r][c];

    // 2*n 비트마스킹
    int totalMask = 1 << (2 * n);
    for (int state = 0; state < totalMask; state++) {
        int cnt = 0;
        memcpy(board, origin, sizeof(board));

        // 0행 상태 확정
        for (int c = 0; c < n; c++) {
            // 회전 횟수
            int rotCnt = (state >> (2 * c)) & 3;
            cnt += rotCnt;

            for (int d = 0; d < 4; d++) {
                int nc = c + dc[d];
                int nr = dr[d];
                if (nc < 0 || nc >= n || nr < 0 || nr >= n) continue;

                board[nr][nc] = (board[nr][nc] + rotCnt) % 4;
            }
        }

        // 1~n-1행 그리디
        for (int r = 1; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (board[r - 1][c] == 0) continue;

                // 윗 행을 0으로 만드는 회전 횟수
                int rotCnt = 4 - board[r - 1][c];
                cnt += rotCnt;
                if (cnt >= answer) break;

                for (int d = 0; d < 4; d++) {
                    int nc = c + dc[d];
                    int nr = r + dr[d];
                    if (nc < 0 || nc >= n || nr < 0 || nr >= n) continue;

                    board[nr][nc] = (board[nr][nc] + rotCnt) % 4;
                }
            }
            if (cnt >= answer) break;
        }

        if (cnt >= answer) continue;

        // 마지막(n-1)행 검증
        bool success = true;
        for (int c = 0; c < n; c++) {
            if (board[n - 1][c]) {
                success = false;
                break;
            }
        }

        if (success) answer = min(cnt, answer);
    }
    
    return answer;
}