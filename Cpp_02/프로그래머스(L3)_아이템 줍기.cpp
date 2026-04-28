// 프로그래머스 L3 : 아이템 줍기
// 조건
// 1. 캐릭터가 이동할 수 있는 경로는 주어진 사각형의 테두리
// 2. 사각형이 겹친 경우 겹친 영역을 제외한 나머지 영역이 이동할 수 있는 경로
// 3. 현재 캐릭터의 위치에서 아이템까지 갈 수 있는 최단 경로
// 풀이
// 1. 좌표 스케일링 (사각형 내부 영역 구현)
//  ex)           0 0 1 1 1 1
//      0 0 0     0 0 1 0 0 1
//      0 1 1  => 0 0 1 0 0 1
//      0 1 1     0 0 1 1 1 1
// 2. bfs
#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;

    // 전체 보드 포맷
    vector<vector<int>> board(101, vector<int>(101, 0)), visited(101, vector<int>(101, 0));
    // 좌표 스케일링 (2배)
    for (auto& seg : rectangle) {
        int x1 = seg[0] * 2, x2 = seg[2] * 2;
        int y1 = seg[1] * 2, y2 = seg[3] * 2;
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                // 사각형 내부
                if (x1 < x && x < x2 && y1 < y && y < y2)
                    board[y][x] = -1;
                else if (board[y][x] != -1)
                    board[y][x] = 1;
            }
        }
    }

    // bfs
    vector<int> dx = { 1,0,-1,0 }, dy = { 0,1,0,-1 };
    queue<pair<int, int>> q;
    q.push({ characterY * 2, characterX * 2 });
    visited[characterY * 2][characterX * 2] = 1;

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        if (cur.first == itemY * 2 && cur.second == itemX * 2) break;

        for (int d = 0; d < 4; d++) {
            int nx = dx[d] + cur.second;
            int ny = dy[d] + cur.first;
            if (nx < 1 || nx > 100 || ny < 1 || ny > 100) continue;
            if (board[ny][nx] != 1) continue;
            if (visited[ny][nx]) continue;

            visited[ny][nx] = visited[cur.first][cur.second] + 1;
            q.push({ ny,nx });
        }
    }

    answer = (visited[itemY * 2][itemX * 2] - 1) / 2;
    return answer;
}