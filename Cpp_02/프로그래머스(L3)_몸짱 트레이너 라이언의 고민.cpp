// 프로그래머스(L3) : 몸짱 트레이너 라이언의 고민(https://school.programmers.co.kr/learn/courses/30/lessons/1838)
// 문제 
// 1. 손님들의 예약시간을 참고해서 되도록 서로 멀리 떨어지도록
//    락커 키를 나눠줘야 함.
// 2. 그 중, 가장 가까웠던 손님 간의 거리를 리턴.
// 조건
// 1. 락커 간 거리 : 상하좌우(1), 대각(2)
// 2. 손님들은 퇴실하는 시간까지 락커를 차지
// 3. 영업시간은 오전 10시부터 오후 10시
// 4. 락커 개수 이상의 손님이 몰리는 경우는 없음.
// 5. 락커 배치 보드(정사각형) 한 변의 길이 n : 0<n<=10
// 6. 손님 수 m : 0<=m<=1,000
// 7. 입/퇴실시간(분 단위) timetable{t1, t2} : 600<=t1<t2<=1,320
//
// 풀이
// 1. 가장 많이 겹치는 사람 수(pq, 그리디)
//  1-1. 정렬 : 입실시간 오름차
//  1-2. pq : 퇴실시간 최소힙
// 2. 구한 수대로 락커에 배치
//  2-1. 이분탐색 :  1 ~ 2*(n-1) 거리로 배치가 가능한지
//  2-2. 배치 가능 여부 (시작점 완탐 0~n-1)
//   2-2-1. 동시에 배치될 수 있는 손님 수 k : 최대 100명(board 크기)
//   2-2-2. 이격 최대 거리 d : 18 = 2*(n-1)
//    최악 : O(log(d) * n^3 * k     
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 최대 배치 수
int getMaxPlaceCount(vector<vector<int>>& timetable) {
    // 입실시간 기준 오름차 정렬
    sort(timetable.begin(), timetable.end(), [](const auto& a, const auto& b) {return a[0] < b[0]; });

    // 퇴실시간 min-heap
    priority_queue<int, vector<int>, greater<int>> pq;

    pq.push(timetable.front()[1]);
    int placeCount = 1;

    for (int i = 1; i < timetable.size(); i++) {
        int inTime = timetable[i][0], outTime = timetable[i][1];

        while (!pq.empty() && inTime > pq.top()) pq.pop();
        pq.push(outTime);

        // 최대 갱신
        placeCount = max(placeCount, (int)pq.size());
    }

    return placeCount;
}

// 보드 내부에 배치가 가능한지
bool canPlace(const int distance, const int placeCount, const int boardSize) {
    vector<pair<int, int>> placed;
    // 0행의 모든 시작지점 확인 
    for (int s = 0; s < boardSize; s++) {
        placed = { {0, s} };
        int remain = placeCount - 1;

        for (int i = s + 1; i < boardSize * boardSize; i++) {
            int r = i / boardSize;
            int c = i % boardSize;

            bool enable = true;
            for (const auto& p : placed) {
                // 맨해튼 거리로 판별
                if (abs(p.first - r) + abs(p.second - c) < distance) {
                    enable = false;
                    break;
                }
            }
            if (!enable) continue;

            placed.push_back({ r,c });
            remain--;
            if (remain == 0) return true;
        }
    }

    return false;
}

int solution(int n, int m, vector<vector<int>> timetable) {
    if (m <= 1) return 0;

    int answer = 0;

    // #1. 동시에 존재하는 최대 인원 구하기(그리디)
    int placeCount = getMaxPlaceCount(timetable);
    if (placeCount <= 1) return 0;
    

    // #2. 배치할 수 있는 최대 거리 구하기
    //   2-1. 거리 이분 탐색 (단조성)
    int lo = 1, hi = 2*(n-1);
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        
        //   2-2. 배치 가능 여부(완탐)
        if (canPlace(mid, placeCount, n)) {
            answer = mid;
            lo = mid + 1;
        }
        else 
            hi = mid - 1;
    }

    return answer;
}