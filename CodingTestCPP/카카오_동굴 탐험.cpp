// 프로그래머스(L4) : 동굴 탐험
// 2020 카카오 인턴십
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

bool BFS(int n, const vector<vector<int>>& graph, vector<int>& before, vector<int>& after)
{
    // 대기열
    unordered_set<int> pending;

    vector<bool> visited(n, false);
    queue<int> q;

    if (before[0] != -1) return false;

    q.push(0);
    visited[0];
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        if (after[cur] != -1)
        {
            int target = after[cur];
            if (pending.find(target) != pending.end())
            {
                q.push(target);
                visited[target] = true;
                pending.erase(target);
            }
        }

        for (int next : graph[cur])
        {
            if (visited[next]) continue;
            if (before[next] != -1 && !visited[before[next]])
            {
                pending.insert(next);
                continue;
            }

            visited[next] = true;
            q.push(next);
        }
    }

    return pending.empty();
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    bool answer = true;

    // 포맷
    vector<vector<int>> graph(n, vector<int>());
    for (const vector<int>& p : path)
    {
        graph[p[0]].push_back(p[1]);
        graph[p[1]].push_back(p[0]);
    }

    vector<int> before(n, -1), after(n, -1);
    for (const vector<int>& o : order)
    {
        before[o[1]] = o[0];
        after[o[0]] = o[1];
    }

    return BFS(n, graph, before, after);
}