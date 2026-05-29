// 프로그래머스(L3) : 양과 늑대
// 입력
// 1. info[i] :0은 양, 1은 늑대, 2<=info.size<=17
// 2. edges : {부모 노드 번호, 자식 노드 번호}
// 3. 0은 항상 루트노드
// 조건
// 1. 양의 수보다 늑대의 수가 같거나 더 많아지면 바로 모든 양을 잡아먹음.
// 풀이
// 1. 상태 DFS, 방문 리스트 공유
//   : 방문한 노드 마스킹 => 방문 가능한 노드 마스킹
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int sheep, int wolf, int visitableMask, int& answer, const vector<int>& info, const vector<vector<int>>& graph) {
    answer = max(answer, sheep);
    if (visitableMask == 0) return;

    for (int i = 0; i < info.size(); i++) {
        if (!(visitableMask & (1 << i))) continue;

        int nSheep = sheep + (info[i] == 0);
        int nWolf = wolf + (info[i] == 1);
        if (nSheep > nWolf) {
            // 방문처리
            int nMask = visitableMask & ~(1 << i);
            // 자식노드 할당
            for (int child : graph[i]) nMask |= (1 << child);
            dfs(nSheep, nWolf, nMask, answer, info, graph);
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer = 0;
    // 그래프 포맷
    int n = info.size();
    vector<vector<int>> graph(n);
    for (auto& e : edges)
        graph[e[0]].push_back(e[1]);

    // 초기상태 : 루트만 방문 가능
    dfs(0, 0, 1, answer, info, graph);
    return answer;
}
