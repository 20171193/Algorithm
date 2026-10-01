// 프로그래머스(L3) : 보물 찾기 (https://school.programmers.co.kr/learn/courses/30/lessons/468378)
// 문제
// 1. 굴착 로봇 
//  1-1. col열을 가능한 최대 깊이만큼 팔 수 있음.
//  1-2. col열에 보물이 있었다면, 보물을 가지고 돌아옴.
//  1-3. col열을 기준으로 왼쪽/오른족 방향에 보물이 있는지 정보를 가지고 돌아옴
//  1-4. 굴착 가능한 깊이만큼 비용이 발생
// 2. excavate 함수
//  2-1. 매개변수 : 굴착할 열
//  2-2. -1 : 보물이 왼쪽 방향에 존재
//  2-3. 0 : 보물을 찾음
//  2-4. 1 : 보물이 오른쪽 방향에 존재
// 3. 수중의 돈 money를 초과하지 않고 보물을 찾아내는 로직 작성
// 풀이
// 1. 그리디 불가 : 데이터 정렬x, 선택지마다 결과가 재각각
// 2. 완탐+역추적
//  2-1. 구간 메모이제이션
//    dp[i][j] : i~j 구간을 확인하는 비용
//  2-2. 역추적
//    path[i][j] : i~j경로에 대해 dp[i][j] 비용을 만드는 경로 인덱스
//   
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

extern int excavate(int);

int solution(vector<int> depth, int money) {
    const int INF_COST = 100000 * 200 + 1;
    const int SIZE = depth.size();

    // 1-based 포맷
    vector<int> d(SIZE + 1);
    copy(depth.begin(), depth.end(), d.begin() + 1);

    vector<vector<int>> dp(SIZE + 1, vector<int>(SIZE + 1, INF_COST)), path(SIZE + 1, vector<int>(SIZE + 1, -1));

    // 최적 경로 할당(dp)
    for (int len = 1; len <= SIZE; len++) {
        for (int s = 1; s <= SIZE - len + 1; s++) {
            int e = s + len - 1;
            if (s == e) {
                dp[s][e] = d[s];
                path[s][e] = s;
                continue;
            }

            int minCost = INF_COST; // 최적 비용
            int pi = s; // 최적 탐색 인덱스
            for (int m = s; m <= e; m++) {
                int leftCost = (m > s) ? dp[s][m - 1] : 0;  // 좌측 포함 비용
                int rightCost = (m < e) ? dp[m + 1][e] : 0; // 우측 포함 비용

                int totalCost = d[m] + max(leftCost, rightCost);
                if (totalCost < minCost) {
                    minCost = totalCost;
                    pi = m;
                }
            }
            dp[s][e] = minCost;
            path[s][e] = pi;
        }
    }

    // 경로 추적
    int l = 1, r = SIZE;
    while (l < r) {
        int pi = path[l][r];

        int dir = excavate(pi);
        if (dir == 0) return pi;

        if (dir == -1) r = pi - 1;
        else l = pi + 1;
    }

    excavate(l);
    return l;
}