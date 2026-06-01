// 프로그래머스(L3) : 등산코스 정하기
// 조건
// 1. 등산코스 : 출입구 출발 → 산봉우리 도달 → 동일 출입구 복귀
// 2. intensity : 코스 중 단일 간선의 최대 가중치
// 3. intensity가 최소인 [산봉우리 번호, intensity] 반환
//   => intensity가 최소인 산봉우리가 2개 이상일 경우 산봉우리 번호가 낮은 순
// 5. 출입구/산봉우리는 경유 불가 (출발·도착·목적지로만 사용)
// 6. 같은 간선 중복 사용 가능
// 7. 임의의 두 지점 사이에 이동 가능한 경로가 항상 존재
// 제한
// - n : 1 ~ 50,000 (지점 번호 1~n)
// - paths 길이 : 1 ~ 200,000 (양방향 간선, [지점A, 지점B, 가중치])
// - gates 길이 : 1 ~ n
// - summits 길이 : 1 ~ n
// - 한 지점은 출입구/산봉우리 중 하나만 해당
// - 간선 가중치 : 1 ~ 10,000,000
// 풀이
// 1. 다익스트라 (코스 중 단일 간선의 최대 가중치)
//  1-1. 최대가 되는 경로로 탐색
//  1-2. 불가능한 경로가 없음
// 2. 완료된 경로 중 최솟값 리턴
// 3. 1-based 노드번호
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int COST_INF = 10000001;

struct Edge {
    int to, cost;
};

vector<int> dijkstra(int n, const vector<int>& gates, const vector<char>& isSummit, const vector<vector<Edge>>& graph) {
    vector<int> dists(n + 1, COST_INF);

    // <cost, to>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // 모든 출입구 삽입
    for (int g : gates) {
        pq.push({ 0, g });
        dists[g] = 0;
    }

    while (!pq.empty()) {
        int curCost = pq.top().first;
        int curNode = pq.top().second;
        pq.pop();

        if (isSummit[curNode] || curCost > dists[curNode]) continue;

        for (const Edge& e : graph[curNode]) {
            int nCost = max(curCost, e.cost);
            if (dists[e.to] <= nCost) continue;

            dists[e.to] = nCost;
            pq.push({nCost, e.to});
        }
    }

    return dists;
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer = {0, 0};

    // 그래프 포맷 graph[from] = {to, cost}, ...
    vector<vector<Edge>> graph(n+1);
    for (const auto& p : paths) {
        graph[p[0]].push_back({ p[1], p[2] });
        graph[p[1]].push_back({ p[0], p[2] });
    }

    vector<char> isSummit(n + 1, 0);
    for (int s : summits) isSummit[s] = 1;

    // 다익스트라
    vector<int> dijCost = dijkstra(n, gates, isSummit, graph);
    
    sort(summits.begin(), summits.end());   // 낮은 번호의 산봉우리 우선
    int minIntensity = COST_INF, summitNum = 0;

    for (int s : summits) {
        if (dijCost[s] < minIntensity) {
            summitNum = s;
            minIntensity = dijCost[s];
        }
    }

    return {summitNum, minIntensity};
}
