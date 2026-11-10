// 프로그래머스(L2) : 배달
// 문제
// 1. 간선비용 : 도로 이동 시간
// 2. 마을의 개수 N, 음식 배달이 가능한 시간 K가 주어짐
// 3. 1번 마을에서 K시간 내 배달이 가능한 마을의 개수를 return
// 조건
// 1. 마을 개수 N : 1<=N<=50
// 2. 도로의 개수 road.size() : 1<=rs<=2,000
//  2-1. road = {a,b,c} 소요 시간(간선 비용)c : 1<=c<=10,000
// 3. 제한시간 K : 1<=K<=500,000
// 풀이
// 1. 다익스트라
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 500001;

// 다익스트라 노드
struct Node {
    int to, cost;
    // 비용 기준 최소힙
    bool operator > (const Node& other) const {
        return cost > other.cost;
    }
};

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;

    // 인접행렬 포맷
    vector<vector<int>> graph(N + 1, vector<int>(N + 1, INF));
    for (auto& r : road) {
        int mn = min({ graph[r[0]][r[1]], graph[r[1]][r[0]], r[2] });

        graph[r[0]][r[1]] = mn;
        graph[r[1]][r[0]] = mn;
    }

    vector<int> dist(N + 1, INF);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[1] = 0;
    pq.push({ 1, 0 });

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        // 이미 더 짧은 거리로 갱신된 낡은 엔트리 무시
        if (cur.cost > dist[cur.to]) continue;

        for (int next = 1; next <= N; next++) {
            if (next == cur.to || graph[cur.to][next] == INF) continue;
            
            int nextCost = cur.cost + graph[cur.to][next];
            // 최소 비용 갱신 및 조건 값 필터링
            if (nextCost > K || nextCost >= dist[next]) continue;
            
            dist[next] = nextCost;
            pq.push({ next, nextCost });
        }
    }

    for (int i = 1; i <= N; i++) 
        answer += dist[i] != INF;

    return answer;
}