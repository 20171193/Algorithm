// 프로그래머스(L4) : 매출 하락 최소화(https://school.programmers.co.kr/learn/courses/30/lessons/72416)
// 문제
// 1. 직원 노드 : {직원 번호, 하루 평균 매출액}
//  1-1. 팀장/팀원 노드 : 부모(팀장)-자식(팀원)이 한 팀
//                      (팀장이자 타 팀원일 수 있음, 1번 노드는 항상 CEO루트)
//  1-2. 한 직원은 최대 2개 팀에 소속될 수 있음. (최대 1명의 부모를 두는 트리 형식)
// 2. 워크숍
//  2-1. 모든 팀은 최소 1명 이상의 직원을 워크숍에 참석시켜야 함.
//  2-2. 워크숍에 참석하는 직원들의 하루 평균 매출액의 합이 최소가 되어야 함.
// 3. 이렇게 최소화된 매출액을 return
// 풀이
// 1. 항상 최소 값을 반환하는 재귀
//   최소 값 : {v가 참석하지 않는 경우, v가 참석하는 경우}
#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

typedef long long ll;

// 현재 num의 참석 여부에 따른 최소 매출액(누적)
// return : {불참, 참석}
pair<ll,ll> dfs(int parent, int num, const vector<int>& sales, const vector<vector<int>>& graph) {
    ll total = 0;

    // 자식이 팀 대표가 될 경우 최소 비용
    ll minChildCost = LLONG_MAX;
    for(auto child : graph[num]) {
        if(child == parent) continue;

        auto p = dfs(num, child, sales, graph);

        ll best = min(p.first, p.second);
        total += best;

        minChildCost = min(minChildCost, p.second - best);  // child자체가 대표가 되는 경우
    }

    // 불참 비용
    ll c1 = graph[num].size() > 1 || num == 1 ? total + minChildCost : 0;

    // 참석 비용
    ll c2 = total + sales[num-1];

    return make_pair(c1, c2);
}

int solution(vector<int> sales, vector<vector<int>> links) {
    ll answer = 0;

    int n = sales.size();
    // 인접 그래프 포맷
    vector<vector<int>> graph(n+1);
    for(auto& link : links){
        graph[link[0]].push_back(link[1]);
        graph[link[1]].push_back(link[0]);
    }

    auto res = dfs(0, 1, sales, graph);
    return answer = min(res.first, res.second);
}
