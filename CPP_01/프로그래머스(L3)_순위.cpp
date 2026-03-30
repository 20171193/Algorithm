#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;

    // 이긴 선수들을 할당
    vector<vector<int>> childs(n + 1);
    // 진 선수들을 할당
    vector<vector<int>> parents(n + 1);

    for (const vector<int>& res : results)
    {
        childs[res[0]].push_back(res[1]);
        parents[res[1]].push_back(res[0]);
    }

    queue<pair<int, bool>> q;
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        int visitCount = 0;

        // 모든 선수에서 bfs 탐색을 수행하며 이긴 선수는 true, 진 선수는 false로 마킹
        // 같은 마킹의 선수만 탐색을 진행.
        //  예시 : (1,2) (1,3)일 경우 1번 선수는 2, 3 선수를 탐색할 수 있지만
        //         2, 3선수는 서로를 탐색할 수 없음. (1번 선수만 탐색가능)  
        q.push({ i,true });
        q.push({ i,false });
        visited[i] = true;

        while (!q.empty())
        {
            int curNode = q.front().first;
            bool curType = q.front().second;
            q.pop();

            for (int next : (curType ? parents[curNode] : childs[curNode]))
            {
                if (visited[next])
                    continue;

                visitCount++;
                visited[next] = true;
                q.push({ next, curType });
            }
        }

        if (visitCount == n - 1)
            answer++;

        fill(visited.begin(), visited.end(), false);
    }

    return answer;
}
