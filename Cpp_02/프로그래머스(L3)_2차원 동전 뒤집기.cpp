// 프로그래머스(L3) : 2차원 동전 뒤집기
// 문제
// 1. 동전 뒤집기 : 특정 행/열의 모든 동전을 뒤집음(반전)
// 2. 보드의 초기 상태에서 목표 상태가 되기까지 최소 몇 번 뒤집기를 수행해야 하는지
// 조건
// 1. 보드 최대 10*10
// 풀이
// 1. DFS + 비트마스킹
//  1-1. DFS : 열을 뒤집는 모든 경우(조합)
//  1-2. 비트마스킹 : 연산 최적화(비교, 반전)
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 101;

class FlipGame {
private:
    int rowLength, colLength, rowFullMask;
    vector<int> originMask, targetMask;

public:
    int bestFlipCount = INF;
    FlipGame(vector<vector<int>>& origin, vector<vector<int>>& target)
    {
        rowLength = origin.size();
        colLength = origin[0].size();

        rowFullMask = (1 << colLength) - 1;

        originMask.resize(rowLength, 0);
        targetMask.resize(rowLength, 0);

        for (int r = 0; r < rowLength; r++) {
            for (int c = 0; c < colLength; c++) {
                originMask[r] |= (origin[r][c] << c);
                targetMask[r] |= (target[r][c] << c);
            }
        }
    }

    void simulation(int col, int flipCnt) {
        if (flipCnt >= bestFlipCount) return;

        auto res = checkMask();
        if (res.first == true)
            bestFlipCount = min(bestFlipCount, flipCnt + res.second);

        for (int next = col + 1; next < colLength; next++) {
            // 뒤집기
            flipColomn(next);
            simulation(next, flipCnt + 1);
            // 원복
            flipColomn(next);
        }
    }

private:
    // 열 반전
    void flipColomn(int c) {
        for (int& bit : originMask)
            bit ^= (1 << c);
    }

    // fst:결과, sec:추가로 뒤집은 행 개수
    pair<bool, int> checkMask(){
        int flipCnt = 0;
        for (int r = 0; r < rowLength; r++) {
            if (originMask[r] == targetMask[r]) continue;
            // 행 반전
            if ((originMask[r] ^ rowFullMask) == targetMask[r]) {
                flipCnt++;
                continue;
            }

            return { false, -1 };
        }

        return { true, flipCnt };
    }
};

int solution(vector<vector<int>> beginning, vector<vector<int>> target) {
    int answer = 0;

    FlipGame game(beginning, target);
    game.simulation(-1, 0);

    answer = game.bestFlipCount;
    return answer == INF ? -1 : answer;
}
