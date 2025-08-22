// 프로그래머스(L3) : 도넛과 막대그래프
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// 도넛 : 사이클 (n, n)
// 막대 : 단방향 (n, n-1)
// 8자 : 동일한 2개의 도넛 결합 (2n+1, 2n+2)

// 출력
// : 1. 생성한 정점 번호
// : 2. 정점 생성이전 도넛 그래프의 수
// : 3. 막대 그래프 수 
// : 4. 8자 그래프 수

// 도넛 : 1 - 2 - 3 - 1 (사이클로 종료)
// 막대 : 1 - 2 - 3
// 8자 : 1 - 2 - 3 - 4 - 5 - 3 - 1 (탐색 도중 사이클 발견)
// 생성한 점 : 두개 이상의 나가는 간선 && 들어오는 간선 = 0

enum OUTPUT_INDEX {
    CREATE = 0,
    DONUT = 1,
    STICK = 2,
    EIGHT = 3
};

// dfs기반
bool IsDonutGraph(int curNode, const vector<vector<int>>& graph, vector<bool>& visited)
{
    if (visited[curNode])
        return true;

    visited[curNode] = true;

    // 연결된 정점이 없는 경우 (막대 그래프)
    if (graph[curNode].size() == 0)
        return false;

    return IsDonutGraph(graph[curNode][0], graph, visited);
}

vector<int> solution(vector<vector<int>> edges) {
    vector<int> answer(4);

    int size = -1;
    for (int i = 0; i < edges.size(); i++)
        size = max({ size, edges[i][0], edges[i][1] });

    // 그래프 포맷
    // 생성한 점 찾기 
    vector<vector<int>> graph(size + 1); //1-based
    vector<bool> isIn(size + 1); // 진입 간선이 연결되었다면 true
    vector<int> candi;  // 진출 간선이 2개 이상인 정점
    for (const vector<int>& edge : edges)
    {
        graph[edge[0]].push_back(edge[1]);
        isIn[edge[1]] = true;

        if (graph[edge[0]].size() > 1)
            candi.push_back(edge[0]);
    }

    vector<bool> visited(size + 1, false);
    // 1. 진출 간선이 두개 이상인 정점을 후보로 등록 
    int startNode = -1;
    for (int node : candi)
    {
        //  2-1. 진입 간선이 있으면 8자 그래프의 순환노드
        //       : 해당 노드와 연결된 노드는 방문체크 후 8자 그래프 개수+1
        if (isIn[node])
        {
            visited[node] = true;
            for (int linkedNode : graph[node])
                IsDonutGraph(linkedNode, graph, visited);

            answer[OUTPUT_INDEX::EIGHT]++;
        }
        //  2-2. 없다면 생성한 점
        //       : 생성한 점과 연결된 점 중 방문하지 않은 정점부터 그래프 확인
        else
        {
            startNode = node;
            answer[OUTPUT_INDEX::CREATE] = startNode;
        }
    }

    visited[startNode] = true;
    for (int next : graph[startNode])
    {
        if (visited[next]) continue;
        if (IsDonutGraph(next, graph, visited))
            answer[OUTPUT_INDEX::DONUT]++;
        else
            answer[OUTPUT_INDEX::STICK]++;
    }

    return answer;
}