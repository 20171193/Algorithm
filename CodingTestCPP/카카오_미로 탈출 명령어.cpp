#include <string>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;

const string fail = "impossible";

int dx[4] = { 1,0,0,-1 };
int dy[4] = { 0,-1,1,0 };
string oper = "dlru";
bool flag = false;

int GetManhattan(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

void dfs(int n, int m, int x, int y, int r, int c, int k, string path, string& answer)
{
    if (flag)
        return;       

    if (k == 0)
    {
        if (x == r && y == c)
        {
            answer = path;
            flag = true;
        }
        return;
    }

    int dist = GetManhattan(x, y, r, c);
    if (dist > k || (k - dist) % 2 == 1)
        return;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m)
            continue;
        dfs(n, m, nx, ny, r, c, k - 1, path + oper[i], answer);
    }
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    int dist = GetManhattan(x, y, r, c);
    if (k < dist || (k - dist) % 2 == 1)
        return fail;

    // 1-based
    dfs(n, m, x - 1, y - 1, r - 1, c - 1, k, "", answer);

    return answer;
}