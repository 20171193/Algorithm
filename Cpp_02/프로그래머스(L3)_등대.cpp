// 프로그래머스(L3) : 등대
// 문제
// 1. n개의 등대와 n-1개의 뱃길로 이루어진 트리
// 2. 모든 뱃길(간선)의 양쪽 끝 등대 중 적어도 하나는 켜져 있어야 함
// 3. 켜야 하는 등대의 최솟값 반환
// 조건
// 1. 등대 개수(노드) : 1<=n<=100,000, 1-based
// 2. 뱃길 개수(간선) : n-1 (트리)
// 풀이
// 1. 위상 정렬 BFS : 리프 노드부터 처리
// 2. 리프(OFF) → 부모 ON, 부모(OFF) → 조부모 OFF 전파
#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(int n, vector<vector<int>> lighthouse) {
    int answer = 0;

    const int EMPTY = 0, ON = 1, OFF = -1;

    vector<vector<int>> graph(n + 1);
    vector<int> degree(n + 1);

    for (auto& lh : lighthouse) {
        graph[lh[0]].push_back(lh[1]);
        graph[lh[1]].push_back(lh[0]);
        degree[lh[0]]++;
        degree[lh[1]]++;
    }

    queue<int> q;
    vector<int> info(n + 1, EMPTY);
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            info[i] = OFF;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        int next = -1;
        for (int node : graph[cur]) {
            if (info[node] == EMPTY) {
                next = node;
                break;
            }
        }

        if (next == -1)
            continue;

        if (info[cur] == OFF) {
            answer++;
            info[next] = ON;
        }
        else
            info[next] = OFF;

        if (--degree[next] == 1)
            q.push(next);
    }

    return answer;
}
