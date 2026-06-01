// 프로그래머스(L3) : 외벽 점검
// 조건
// 1. 원형 외벽(둘레 n미터)의 취약 지점(weak)을 친구들이 1시간 안에 모두 점검
// 2. 각 친구는 dist[i] 거리만큼 시계 또는 반시계 방향으로 이동 가능
// 3. 취약 지점을 모두 점검하는 데 필요한 최소 친구 수 반환
// 4. 모두 투입해도 불가능하면 -1 반환
// 제한
// - n : 1 ~ 200
// - weak 길이 : 1 ~ 15 (오름차순 정렬)
// - dist 길이 : 1 ~ 8
// - dist 원소 : 1 ~ 100
// 풀이
// 1. dist 순열 : 8!
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {    
    // 2배 배열(원형)
    vector<int> extended = weak;
    for (int i = 0; i < weak.size(); i++)
        extended.push_back(weak[i]+n);


    int pepLength = dist.size(), targetLength = weak.size();
    // 초기값 설정
    int answer = pepLength + 1;
    sort(dist.begin(), dist.end());
    do {
        int pepIdx = 0, covered = 0;
        for (int start = 0; start < targetLength; start++) {
            bool flag = false;
            int cur = start, pepIdx = 0, covered = 0;

            while (pepIdx < pepLength) {
                covered = extended[cur] + dist[pepIdx];

                // 다음 커버할 영역까지 점프
                while (cur < extended.size() && extended[cur] <= covered) cur++;
                
                // 모든 영역을 커버한 경우
                if (cur - start >= targetLength) {
                    flag = true;
                    break;
                }

                pepIdx++;
            }

            // pepIdx+1 => 배치한 수
            if (flag) answer = min(answer, pepIdx + 1);
        }
    } while (next_permutation(dist.begin(), dist.end()));   // 정렬된 입력

    return answer == pepLength + 1 ? -1 : answer;
}