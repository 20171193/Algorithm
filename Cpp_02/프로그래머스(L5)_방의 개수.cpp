// 프로그래머스(L5) : 방의 개수
// 조건
// 1. 방향
//  : 상  / 우상 / 우  / 우하 / 하  / 좌하 /  좌 / 좌상
//    7 0 1
//    6   2
//    5 4 3
// 
// 2. 방향대로 그림을 그리며 사방이 막히면 방하나로 샘.
// 풀이
// 1. 평면 그래프 공식
//   V - E + F = 2
//           F = 2 + E - V - 1(외부 영역 제외)
#include <string>
#include <vector>
#include <set>
using namespace std;

int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
int dy[8] = { 1,1,0,-1,-1,-1,0,1 };

pair<int, int> operator+(const pair<int, int>& pos, int dir) {
    return { pos.first + dx[dir], pos.second + dy[dir] };
}

int solution(vector<int> arrows) {
    set<pair<int, int>> vtx;  // 꼭짓점 : V
    set<pair<pair<int, int>, pair<int, int>>> edge;   // 간선 : E

    pair<int, int> cur = { 0,0 };
    for (int arrow : arrows) {
        // 좌표 스케일링
        for (int dist = 0; dist < 2; dist++) {
            auto next = cur + arrow;

            vtx.insert({ cur });
            // 정규화
            edge.insert(cur < next ? make_pair(cur, next) : make_pair(next, cur));
            cur = next;
        }
    }

    vtx.insert(cur);

    // F = E - V + 1
    return edge.size() - vtx.size() + 1;
}