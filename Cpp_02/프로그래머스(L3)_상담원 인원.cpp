// 프로그래머스(L3) : 상담원 인원
// 문제
// 1. n명의 멘토, 1~k의 상담 유형 존재. 각 멘토는 k개 상담 유형 중 하나만 담당 가능.
// 2. 멘토는 동시에 한 명과 상담 가능하며, 상담자가 요청한 시간만큼 상담 시간이 소요됨.
// 3. 멘토는 먼저 상담을 요청한 참가자를 우선 상담
// 조건
// 1. 상담 유형 k : 1<=k<=5
// 2. 멘토 수 n : k<=n<=20
// 3. 상담 요청 reqs : 3<=reqs.size()<=300
//  3-1. 상담 요청시작 시각 reqs[0], a : 1<=a<=1,000
//  3-2. 상담 시간 reqs[1], b : 1<=b<=100
//  3-3. 상담 유형 reqs[2], c : 1<=c<=k
//  *reqs는 a를 기준으로 오름차순 정렬되어 있음.
//  *reqs의 a는 중복되지 않음. 즉, 요청시작한 시각은 모두 다름
// 풀이
// 1. n명의 멘토를 k개 유형에 각각 배치하는 모든 경우의 수
//  : 5H15 = 19C15 = 3.876(k에 마다 1명씩 배치 후 중복 조합)
#include <string>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int K, N;


int calcDelay(const vector<int>& typeAssigned, const vector<vector<pair<int,int>>>& typeReqs){
    int totalDelay = 0;

    priority_queue<int, vector<int>, greater<int>> endTimeMinFirstQ;
    for(int type = 1; type < typeAssigned.size(); type++){

        for(int c = 0; c < typeAssigned[type]; c++) endTimeMinFirstQ.push(0);

        for(auto& req : typeReqs[type]) {
            int curTime = endTimeMinFirstQ.top();
            int endTime = 0;

            if(curTime > req.first) {
                totalDelay += curTime - req.first;
                endTime = curTime + req.second;
            }
            else
                endTime = req.first + req.second;

            endTimeMinFirstQ.pop();
            endTimeMinFirstQ.push(endTime);
        }

        while(!endTimeMinFirstQ.empty()) endTimeMinFirstQ.pop();
    }

    return totalDelay;
}

void dfs(int type, int totalAssign, vector<int>& typeAssigned, const vector<vector<pair<int,int>>>& typeReqs, int& answer){
    if (type == K){
        // 마지막 유형에는 남은 모든 멘토 배정
        typeAssigned[type] = N - totalAssign;

        answer = min(answer, calcDelay(typeAssigned, typeReqs));
        return;
    }

    // 최소 한 명씩 배치하기 위한 최대 값
    int maxAssign = N - totalAssign - (K - type);
    for(int count = 1; count <= maxAssign; count++) {
        typeAssigned[type] = count;

        dfs(type+1, totalAssign + count, typeAssigned, typeReqs, answer);
    }
}

int solution(int k, int n, vector<vector<int>> reqs) {
    int answer = INT_MAX;

    K = k;
    N = n;

    // 타입 별로 재정렬
    vector<vector<pair<int,int>>> typeReqs(k+1);
    for(auto& r : reqs) typeReqs[r[2]].push_back({r[0], r[1]});

    vector<int> typeAssigned(k+1);
    dfs(1, 0, typeAssigned, typeReqs, answer);

    return answer;
}
