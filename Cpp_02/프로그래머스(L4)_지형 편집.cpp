// 프로그래머스(L4) : 지형 편집
// 문제
// 1. 지형의 높이가 같아지도록 만들어야 함.
// 2. 지형 추가 비용 : P
// 3. 지형 제거 비용 : Q
// 풀이
// 1. 최대 비용 :  10^15 * 9 { (P/Q)10^2 * (land[i])10^9 * (land size)9*10^4 } 
// 2. 높이 기준 이분탐색
//  2-1. mid와 mid+1 비교 후 상향 or 하향
// 최적화
// 1. 높이 별 prefix sum
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;

typedef long long ll;

ll GetEditCost(int targetFloor, int P, int Q, const vector<int>& heights, const vector<ll>& prfHeights){
    ll result = 0;

    auto findIter = upper_bound(heights.begin(), heights.end(), targetFloor);
    int mid = findIter - heights.begin();

    // targetFloor보다 낮은 층 개수(lc), 높은 층 개수(rc) 
    int lc = mid, rc = heights.size() - mid;
    // 낮은 층 높이 합, 높은 층 높이 합
    ll lsum = prfHeights[mid];
    ll rsum = prfHeights.back() - lsum;

    return P * ((ll)lc * targetFloor - lsum) + Q * (rsum - (ll)rc * targetFloor);
}

ll solution(vector<vector<int>> land, int P, int Q) {
    ll answer = LLONG_MAX;

    // 높이 기준 1차원 정렬
    vector<int> heights(land.size() * land[0].size());
    int idx = 0;
    for(auto& r : land)
        for(auto h : r) 
            heights[idx++] = h;

    sort(heights.begin(), heights.end());

    // 높이 누적합
    vector<ll> prfHeights(heights.size() + 1);
    prfHeights[0] = 0;
    for(int i = 0; i< heights.size(); i++)
        prfHeights[i+1] = prfHeights[i] + heights[i];
    

    // 이분 탐색
    int l = 0, r = 1000000000;
    while(l < r){
        
        int mid = (l + r) >> 1;
        ll cost1 = GetEditCost(mid, P, Q, heights, prfHeights);
        ll cost2 = GetEditCost(mid+1, P, Q, heights, prfHeights);
        
        answer = min(answer, min(cost1, cost2));
        
        if(cost1 < cost2) r = mid;
        else l = mid + 1;
    }
    
    return answer;
}