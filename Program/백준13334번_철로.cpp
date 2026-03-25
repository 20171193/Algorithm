// 백준 13334번 : 철로
// 조건
// 1. 철로는 집과 사무실(h, o)라는 선분을 모두 포함해야 함.
// 2. 최대한 많은 선분을 포함하게 배치했을 때, 포함되는 선분의 개수
// 3. 사람의 수n(1<=n<=100,000)
// 4. 집과 사무실의 위치 h, o(-(10^8)<=h, o<=10^8)
// 5. 철로의 길이 d(1<=d<=10^8)
// 풀이
// 1. 위치 정렬(선분화)
// 2. 우선 순위 큐, 구간 쳐내기
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, d;
vector<pair<int, int>> segs;

int solution() {
    // 우측 끝 기준 오름차 정렬
    sort(segs.begin(), segs.end(), [](auto& a, auto& b){
        if(a.second == b.second) return a.first < b.first;
        else return a.second < b.second;       
    });

    int ret = 0;
    priority_queue<int, vector<int>, greater<int>> pq;  

    for (const auto& seg : segs) {
        int l = seg.first;
        int r = seg.second;
        if(r - l > d) continue;

        // 왼쪽 끝만 할당
        pq.push(l);
        
        while (!pq.empty() && r - pq.top() > d) pq.pop(); 
        ret = max(ret, (int)pq.size());
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // input
    cin >> n;
    segs.assign(n, { 0,0 });
    for (int i = 0; i < n; i++) {
        cin >> segs[i].first >> segs[i].second;
        if (segs[i].first > segs[i].second)
            swap(segs[i].first, segs[i].second);
    }
    cin >> d;

    cout << solution() << '\n';
    return 0;
}