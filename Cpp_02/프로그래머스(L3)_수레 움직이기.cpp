// 프로그래머스(L3) : 수레 움직이기
// 문제
// 1. 빨간/파란 수레를 각 도착 칸으로 옮기는 최소 턴
// 2. 턴 : 반드시 모든 수레를 인접한 칸으로 움직여야 함.
// 조건
// 1. 방문했던 칸은 이동 불가(색상이 다르면 가능)
// 2. 도착 칸에 도착한 수레는 움직일 수 없음.
// 3. 동시에 두 수레가 같은 칸으로 이동 불가.
// 4. 수레끼리 자리를 바꾸며 이동 불가.
// 5. 보드 N*M(1<=N,M<=4)
// 6. 0(빈칸), 1(빨간 수레 시작), 2(파란 수레 시작),
//    3(빨간 수레 도착), 4(파란 수레 도착), 5(벽)
// 풀이
// 1. bfs + 상태메모이제이션
//  1-1. 비트마스킹 방문상태 (uint)
//     빨간 수레(0~15), 파란 수레(16~31)
#include <string>
#include <vector>
#include <queue>
#include <cstdint>
#include <unordered_map>
using namespace std;

const enum CELL_TYPE { EMPTY = 0, RED_START, BLUE_START, RED_END, BLUE_END, WALL };

// 32비트
typedef uint32_t uint;

int ROW, COL, SHIFT;
uint FULL_MASK;

int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};

struct State {uint rIdx, bIdx, visitedMask;};

uint PosToIndex(pair<int, int> pos){
    return (uint)(pos.first * COL + pos.second);
}

pair<int, int> IndexToPos(uint index){
    return {(int)index / COL, (int)index % COL};
}

pair<pair<int,int>, pair<int,int>> IndexToPos(uint rIdx, uint bIdx){
    return {IndexToPos(rIdx), IndexToPos(bIdx)};
}

// 범위 검증, 벽 검증, 재방문 검증
vector<pair<uint, uint>> GetNextStates(bool isRed, pair<uint, uint> curState, const vector<vector<int>>& maze){
    vector<pair<uint, uint>> result;

    uint curIdx = curState.first;
    auto curPos = IndexToPos(curIdx);

    uint curMask = curState.second;

    for(int d = 0; d < 4; d++){
        auto nextPos = make_pair(curPos.first + dy[d], curPos.second + dx[d]);
        if(nextPos.first < 0 || nextPos.first >= ROW || nextPos.second < 0 || nextPos.second >= COL) continue;
        if(maze[nextPos.first][nextPos.second] == WALL) continue;

        uint nextIdx = PosToIndex(nextPos);
        uint nextMask = ((uint)1 << nextIdx) << (isRed ? 0 : SHIFT);

        if(nextMask & curMask) continue;    // 이미 방문한 경로

        result.push_back({nextIdx, nextMask | curMask});
    }

    return result;
}

int solution(vector<vector<int>> maze){
    ROW = maze.size();
    COL = maze[0].size();
    SHIFT = ROW * COL;
    FULL_MASK = ((uint)1 << (ROW * COL * 2)) -1;

    uint rStart = -1, bStart = -1, rEnd = -1, bEnd = -1;
    for (int r = 0; r < ROW; r++){
        for (int c = 0; c < COL; c++){
            int cell = maze[r][c];
            if (EMPTY < cell && cell < WALL){
                int cell_index = PosToIndex({r, c});

                if (cell == RED_START) rStart = cell_index;
                else if (cell == BLUE_START) bStart = cell_index;
                else if (cell == RED_END) rEnd = cell_index;
                else bEnd = cell_index;
            }
        }
    }

    // <visitedMask, turn_count>
    unordered_map<uint, int> visited;

    // State : nextMask, visitedMask
    queue<State> q;

    uint startMask = ((uint)1 << rStart) | (((uint)1 << bStart) << SHIFT);
    visited[startMask] = 0;
    q.push({rStart, bStart, startMask});

    while(!q.empty()){
        auto cur = q.front();
        uint rIdx = cur.rIdx;
        uint bIdx = cur.bIdx;
        uint mask = cur.visitedMask;

        auto [rPos, bPos] = IndexToPos(rIdx, bIdx);
        q.pop();

        // 각 수레의 다음 상태할당
        vector<pair<uint, uint>> nrState, nbState;
        if(rIdx == rEnd) nrState = {{rIdx, mask}};
        else nrState = GetNextStates(true, {rIdx, mask}, maze);

        if(bIdx == bEnd) nbState = {{bIdx, mask}};
        else nbState = GetNextStates(false, {bIdx, mask}, maze);

        // 두 상태 조합 (+ 교차 이동 검증, 동일 좌표 검증, 도착 검증)
        for(const auto& [nrIdx, nrMask] : nrState) {
            for(const auto& [nbIdx, nbMask] : nbState){
                // 교차 이동 / 동일 좌표 검증
                if((nrIdx == bIdx && nbIdx == rIdx) || (nrIdx == nbIdx)) continue;
                // 두 수레 모두 도착 - 탐색 바로 종료
                if(nrIdx == rEnd && nbIdx == bEnd) return visited[mask] + 1;

                uint nextMask = nrMask | nbMask;
                if(visited.find(nextMask) == visited.end()){
                    visited[nextMask] = visited[mask] + 1;
                    q.push({nrIdx, nbIdx, nextMask});
                }
            }
        }
    }

    return 0;
}
