// ���α׷��ӽ�(L3) : ���ַ� �Ǽ�
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
// ���� �� 100��
// ���� ������ �ٲ� �� +500��

// 1. �ּ� ���� ����
// 2. �ּ� ��� ����(���� ��ȯ)
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
    // ���� 1 ���ַ� �Ǽ�
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
            // �ݴ� �����̵� ���� (�̹� �Ǽ��� ���ַ�)
            if (i == (cur.dir + 2) % 4) continue;
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            // ���� ó��
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            // �� ó��
            if (board[ny][nx] == 1) continue;
            // ��� ó��
            int ncost = cur.cost + (cur.dir == i ? 1 : 6);
            if (visited[ny][nx][i] && visited[ny][nx][i] <= ncost) continue;

            visited[ny][nx][i] = ncost;
            if (ny == n - 1 && nx == n - 1)
                answer = min(answer, ncost);
            else
            {
                // Ž�� ����ȭ (����ġ��)
                if (answer <= ncost) continue;
                q.push({ ny,nx,ncost,i });
            }
        }
    }

    return answer * 100;
}