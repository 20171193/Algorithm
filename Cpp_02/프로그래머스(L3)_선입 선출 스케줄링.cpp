// 프로그래머스(L3) : 선입 선출 스케줄링
// 문제
// 1. 처리시간이 각각 다른 여러 개의 코어가 존재
// 2. 코어 간 워크스틸링 (앞의 코어부터 작업 처리)
// 조건
// 1. 작업 개수 (1<=n<=50,000)
// 2. 코어 개수 (2<=cores.size<=10,000)
// 3. 코어당 처리시간 (1<=cores[i]<=10,000)
// 출력
// 1. 마지막 작업을 처리하는 코어의 번호 return
// 풀이
// 1. 우선순위 큐 - 효율성 실패
// 2. 이분탐색
//  2-1. 작업 시간 구하기 : n개 이상의 작업을 처리할 수 있는 최소 t초(작업 시간)
//  2-2. 마지막으로 작업을 수행한 코어 인덱스 구하기 t%i == 0
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

ll ProcessCount(int time, const vector<int>& cores) {
    ll ret = cores.size(); // 0초 배정 포함
    for (int c : cores) ret += time / c;
    return ret;
}

int solution(int n, vector<int> cores) {
    if (n <= cores.size()) return n;

    int answer = 0;
    int lo = 0, hi = 500000000;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (ProcessCount(mid, cores) >= n) 
            hi = mid - 1;
        else 
            lo = mid + 1;
    }

    // 직전(lo - 1)에 수행된 작업 개수 제외
    int remain = n - (int)ProcessCount(lo - 1, cores);
    for (int i = 0; i < cores.size(); i++) {
        if (lo % cores[i] == 0) {
            if (--remain == 0) {
                answer = i + 1;
                break;
            }
        }
    }
    
    return answer;
}

int main() {
    solution(6, { 1,2,3 });
    return 0;
}