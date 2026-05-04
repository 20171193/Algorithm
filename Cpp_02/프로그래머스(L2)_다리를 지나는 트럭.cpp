// 프로그래머스(L2) : 다리를 지나는 트럭
// 조건
// 1. bride_length(1<=bl<=10,000) 
//   : 트럭이 올라갈 수 있는 개수, 트럭이 다리를 통과하는 데 걸리는 시간
// 2. weight(1<=w<=10,000) : 트럭이 견딜 수 있는 무게
// 3. truck_weights(1<=tw<=10,000) : 트럭의 무게
// 풀이
// 1. 현재 시간, 트럭 무게 누적
// 2. queue<pair<int,int>> : 트럭 무게, 놓은 시점
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;

    int total = 0, curTime = 0;
    queue<pair<int, int>> q;
    for (auto w : truck_weights) {
        curTime++;

        // 지나간 트럭 처리
        while (!q.empty() && q.front().second + bridge_length <= curTime) {
            total -= q.front().first;
            q.pop();
        }

        // 트럭을 놓지 못하는 경우
        while (total + w > weight || q.size() > bridge_length) {
            total -= q.front().first;
            // 타임스텝 점프
            curTime = q.front().second + bridge_length;

            q.pop();
        }

        total += w;
        q.push({ w, curTime });
    }

    // 마지막 남은 트럭 기준
    while (q.size() > 1) q.pop();

    return answer = q.front().second + bridge_length;
}