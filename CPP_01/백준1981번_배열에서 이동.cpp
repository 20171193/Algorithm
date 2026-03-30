// 백준 1981번 : 배열에서 이동
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int INF = 201;
int n, minNum = INF, maxNum = -1, arr[101][101];
bool visited[101][101];

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

bool BFS(int mn, int mx)
{
    if (arr[0][0] < mn || arr[0][0] > mx)
        return false;

    fill(&visited[0][0], &visited[0][0] + 101 * 101, false);

    queue<pair<int, int>> q;
    q.push({ 0, 0 });
    visited[0][0] = true;

    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();

        if (cur.first == n - 1 && cur.second == n - 1) return true;

        for (int d = 0; d < 4; d++)
        {
            int ny = cur.first + dy[d];
            int nx = cur.second + dx[d];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
            if (visited[ny][nx]) continue;
            if (arr[ny][nx] < mn || arr[ny][nx] > mx) continue;

            visited[ny][nx] = true;
            q.push({ ny, nx });
        }
    }
    return false;
}

int solution()
{
    int answer = INF;
    // 가능한 범위내에서 이분탐색
    for (int low = minNum; low <= maxNum; low++)
    {
        int l = low;
        int r = maxNum;
        int differ = -1;

        // 이분 탐색
        while (l <= r) {
            int mid = (l + r) / 2;
            if (BFS(low, mid)) {
                differ = mid - low;
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }

        if (differ != -1)
            answer = min(answer, differ);
    }

    return answer;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
            minNum = min(arr[i][j], minNum);
            maxNum = max(arr[i][j], maxNum);
        }
    }

    cout << solution() << '\n';
    return 0;
}