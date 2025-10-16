// 프로그래머스(L3) : 경주로 건설
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
// 간선 당 100원
// 간선 방향이 바뀔 때 +500원

// 1. 최소 간선 도착
// 2. 최소 비용 도착(방향 전환)
using namespace std;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

struct Node {
    int y, x, cost, dir;
};
int solution(vector<vector<int>> board) {
    int answer = INT_MAX;
    int n = board.size();
    vector<vector<vector<int>>> visited(n, vector<vector<int>>(n, vector<int>(4)));
    queue<Node> q;
    // 길이 1 경주로 건설
    if (board[0][1] != 1)
    {
        q.push({ 0,1,1,0 });
        visited[0][1][0] = 1;
    }
    if (board[1][0] != 1)
    {
        q.push({ 1,0,1,1 });
        visited[1][0][1] = 1;
    }

    // BFS
    while (!q.empty())
    {
        Node cur = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            // 반대 방향이동 제외 (이미 건설된 경주로)
            if (i == (cur.dir + 2) % 4) continue;
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            // 범위 처리
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            // 벽 처리
            if (board[ny][nx] == 1) continue;
            // 비용 처리
            int ncost = cur.cost + (cur.dir == i ? 1 : 6);
            if (visited[ny][nx][i] && visited[ny][nx][i] <= ncost) continue;

            visited[ny][nx][i] = ncost;
            if (ny == n - 1 && nx == n - 1)
                answer = min(answer, ncost);
            else
            {
                // 탐색 최적화 (가지치기)
                if (answer <= ncost) continue;
                q.push({ ny,nx,ncost,i });
            }
        }
    }

    return answer * 100;
}