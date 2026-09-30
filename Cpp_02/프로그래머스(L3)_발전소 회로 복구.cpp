// 프로그래머스(L3) : 발전소 회로 복구
// 문제
// 1. n*m*h 형태의 건물
// 2. 통로 중 k곳에는 서로 다른 번호를 가진 회로 패널이 설치됨.(비활성화 상태)
// 3. 인접한 칸 이동 시 1초 소모, 엘리베이터로 층 간 이동 시 (목표층-현재층)초 소모
// 4. 안전 순서에 따른 패널을 활성화 해야함. 
//    안전 순서 : [a, b]쌍 -> a먼저 활성화해야 b활성화 가능
// 조건
// 1. 층 h : 1<=h<=10
// 2. 그리드 길이 grid : 1<=grid<=40
// 3. 패널 길이(패널 위치 정보) k : 1<=k<=15
// 4. 안전 순서 길이 seqs : 1<=seqs<=100
// 
// 풀이
// 1. 패널 진입조건 비트마스크
// 2. 모든 패널 간 거리 할당(BFS)
//    +각 패널에서 엘리베이터까지 거리 할당
// 3. 최단 경로 탐색(다익스트라)
// 
// 수정
// 1. 시간초과 해결 : 최단 경로 탐색(BFS -> 다익스트라)
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

int MAX_ROW, MAX_COL, PANEL_COUNT, FULL_MASK;

int dc[4] = { 1,0,-1,0 };
int dr[4] = { 0,1,0,-1 };

// 다익스트라 노드
struct State {
    int panel, mask, dist;
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

void bfs(int r, int c, vector<vector<int>>& visited, const vector<string>& grid) {
    for (auto& row : visited)
        fill(row.begin(), row.end(), 0);

    queue<pair<int, int>> q;
    q.push({ r,c });
    visited[r][c] = 0;

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = cur.first + dr[d];
            int nc = cur.second + dc[d];
            if (nr < 0 || nr >= MAX_ROW || nc < 0 || nc >= MAX_COL) continue;
            if (grid[nr][nc] == '#') continue;
            if (visited[nr][nc]) continue;

            visited[nr][nc] = visited[cur.first][cur.second] + 1;
            q.push({ nr,nc });
        }
    }
}

int solution(int h, vector<string> grid, vector<vector<int>> panels, vector<vector<int>> seqs) {
    // 전역 변수 할당
    MAX_ROW = grid.size();
    MAX_COL = grid[0].size();
    PANEL_COUNT = panels.size();
    FULL_MASK = (1 << (PANEL_COUNT + 1)) - 2;

    int answer = INT_MAX;
    // --- 1. 진입조건 비트마스크
    vector<int> seqMask(PANEL_COUNT + 1);
    for (const auto& seq : seqs)
        seqMask[seq[1]] |= (1 << seq[0]);

    // --- 2. 패널 간 거리 할당(행렬 BFS)
    // 엘리베이터 to 패널
    vector<int> distToEV(PANEL_COUNT + 1);
    bool flag = false;
    for (int r = 0; r < MAX_ROW; r++) {
        for (int c = 0; c < MAX_COL; c++) {
            if (grid[r][c] == '@') {
                vector<vector<int>> visited(MAX_ROW, vector<int>(MAX_COL));
                bfs(r, c, visited, grid);

                for (int to = 1; to <= PANEL_COUNT; to++)
                    distToEV[to] = visited[panels[to - 1][1] - 1][panels[to - 1][2] - 1];

                flag = true;
                break;
            }
        }
        if (flag) break;
    }

    // 패널 to 패널
    vector<vector<int>> dists(PANEL_COUNT + 1, vector<int>(PANEL_COUNT + 1));
    vector<vector<int>> visitedGrid(MAX_ROW, vector<int>(MAX_COL));

    for (int from = 1; from <= PANEL_COUNT; from++) {
        vector<int>& fromPos = panels[from - 1];

        bfs(fromPos[1] - 1, fromPos[2] - 1, visitedGrid, grid);

        for (int to = 1; to <= PANEL_COUNT; to++) {
            if (from == to) continue;
            vector<int>& toPos = panels[to - 1];

            if (fromPos[0] == toPos[0])
                dists[from][to] = dists[to][from] = visitedGrid[toPos[1] - 1][toPos[2] - 1];
            // 층이 다를 경우 : (from to 엘베) + (층 diff) + (to to 엘베) 
            else
                dists[from][to] = dists[to][from] = distToEV[from] + distToEV[to] + abs(toPos[0] - fromPos[0]);
        }
    }


    // --- 3. 최단 경로 탐색
    // <panel, mask>
    priority_queue<State, vector<State>, greater<State>> pq;
    // [i][mask] : i번 패널을 mask 상태로 방문한 최단 거리
    vector<vector<int>> visited(PANEL_COUNT + 1, vector<int>(FULL_MASK + 1));

    // 최초 위치 : 1번 패널
    int initMask = seqMask[1] == 0 ? 2 : 0;
    pq.push({1, initMask, 0});
    visited[1][initMask] = 0;

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        if (cur.dist > visited[cur.panel][cur.mask]) continue;
        if (cur.mask >= FULL_MASK) {
            answer = min(answer, cur.dist);
            continue;
        }

        for (int nextPanel = 1; nextPanel <= PANEL_COUNT; nextPanel++) {
            if (cur.panel == nextPanel) continue;
            // 현재 스텝에 이미 방문
            if (cur.mask & (1 << nextPanel)) continue;
            // 진입 조건 미충족
            if ((cur.mask & seqMask[nextPanel]) != seqMask[nextPanel]) continue;

            int nextMask = cur.mask | (1 << nextPanel);
            int nextDist = cur.dist + dists[cur.panel][nextPanel];
            // 더 좋은 조건으로 이미 방문
            if (visited[nextPanel][nextMask] && visited[nextPanel][nextMask] <= nextDist) continue;

            visited[nextPanel][nextMask] = nextDist;
            pq.push({ nextPanel, nextMask ,nextDist });
        }
    }

    return answer;
}
