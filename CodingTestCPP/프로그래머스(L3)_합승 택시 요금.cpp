#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
using namespace std;

// s, e, c

struct Comparer {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return a.second > b.second;
    }
};

vector<int> Dijkstra(int n, int start, const vector<vector<pair<int, int>>>& edges)
{
    vector<int> dists(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparer> pq;
    dists[start] = 0;
    pq.push({ start, 0 });

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();

        // <도착노드, 누적 비용>
        for (auto& p : edges[cur.first])
        {
            if (dists[p.first] > dists[cur.first] + p.second)
            {
                dists[p.first] = dists[cur.first] + p.second;
                pq.push({ p.first, dists[p.first] });
            }
        }
    }

    return dists;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INT_MAX;

    // 간선 포맷
    vector<vector<pair<int, int>>> edges(n + 1);
    for (const vector<int>& f : fares)
    {
        edges[f[0]].push_back({ f[1], f[2] });
        edges[f[1]].push_back({ f[0], f[2] });
    }

    // 다익스트라
    vector<int> sDists = Dijkstra(n, s, edges);
    vector<int> aDists = Dijkstra(n, a, edges);
    vector<int> bDists = Dijkstra(n, b, edges);

    // 모든 경유지 노드확인
    for (int i = 1; i <= n; i++)
        answer = min(answer, sDists[i] + aDists[i] + bDists[i]);

    return answer;
}