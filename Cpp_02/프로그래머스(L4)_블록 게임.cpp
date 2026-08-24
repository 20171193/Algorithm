// 프로그래머스(L4) : 블록 게임
// 문제
// 1. 1*1짜리 블록을 '위'에서 떨어뜨려 없앨 수 있는 블록의 최대 개수
//   : 속이 꽉찬 직사각형을 만들면 없어짐.
// 풀이
// 1. 같은 열, 윗 행에 블록이 존재하면 절대 삭제할 수 없는 구조.
//  1-1. 같은 '열'을 공유하는 블록 간 인접 그래프
//  1-2. 진입 차수 : 이전 행 블록이 다음 행 블록의 진입 조건
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <iostream>
using namespace std;

// TODO
// : 현재 문제에서는 주어지지 않는 형태지만,
//   다음과 같은 형태에서는 현재 판단으로 불가.
// : => 더 적절한 방법 고민
// EX) 000
//     0 0

bool CanDestroy(vector<pair<int,int>>& block) {
    sort(block.begin(), block.end(), [](const auto& a, const auto& b){
        if(a.first == b.first) return a.second < b.second;
        return a.first > b.first;
    });

    vector<pair<int,int>> rowRange;
    int prevRow = -1;
    int idx = -1;
    for(auto p : block){
        if(prevRow != p.first){
            rowRange.push_back({p.second, p.second});
            prevRow = p.first;
            idx++;
        }
        else
            rowRange[idx].second = p.second;

        if(idx > 0){
            if(!(rowRange[idx-1].first <= rowRange[idx].first 
                && rowRange[idx].second <= rowRange[idx-1].second))
                return false;
        }
    }

    return true;
}

int solution(vector<vector<int>> board) {
    int answer = 0;

    const int MAX_NODE = 200;
    int n = board.size();

    vector<vector<pair<int,int>>> blocks(MAX_NODE+1);

    // 인접 그래프
    vector<vector<int>> graph(MAX_NODE + 1);
    // 간선 할당 여부
    vector<vector<bool>> linked(MAX_NODE + 1, vector<bool>(MAX_NODE + 1, false));
    // 노드 별 진입 차수
    unordered_map<int, int> indegree;

    // 해당 열에 마지막으로 등장했던 블록 수
    vector<int> colPrevNum(n);

    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
            if(board[r][c]) {
                int cur = board[r][c];
                blocks[cur].push_back(make_pair(r,c));

                int prev = colPrevNum[c];
                if(!prev && indegree.find(cur) == indegree.end())
                    indegree[cur] = 0;
                else if(prev && prev != cur){
                    if(!linked[prev][cur]) {
                        indegree[cur]++;
                        // 단방향 간선 할당
                        graph[prev].push_back(cur);
                        linked[prev][cur] = true;
                        linked[cur][prev] = true;
                    }
                }
                
                colPrevNum[c] = cur;
            }   
        }
    }

    queue<int> q;
    for(auto iter = indegree.begin(); iter != indegree.end(); iter++){
        cout << "indegree : " << (*iter).first << " = " << (*iter).second << '\n';
        
        if((*iter).second == 0){
            q.push((*iter).first);
        }
    }
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();

        // 현재 블럭이 지워질 수 있는 모양인지 판단
        if(!CanDestroy(blocks[cur])) {
            cout << cur << " : can't destroy" << '\n';
            continue;
        }

        cout << cur << " : can destroy" << '\n';
        answer++;
        for(auto next : graph[cur]){
            indegree[next]--;

            if(indegree[next] == 0) q.push(next);
        }
    }

    return answer;
}