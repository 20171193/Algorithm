#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

bool cmp(vector<int>& a, vector<int>& b)
{
    if (a[0] == b[0])
        return a[1] < b[1];

    return a[0] < b[0];
}

int solution(vector<vector<int>> routes) {
    int answer = 0;

    // 경로의 시작지점 기준 오름차순 정렬
    sort(routes.begin(), routes.end(), cmp);
    // 공통 구간 설정
    int commonStart = routes[0][0];
    int commonEnd = routes[0][1];

    // 카메라를 적어도 한 대는 놓고 진행
    answer = 1;

    for (int i = 1; i < routes.size(); i++)
    {
        /// 현재 경로 기준으로 공통 경로 재설정
        // 공통된 경로의 도착지점보다 현재 경로의 시작지점이 클 경우
        if (commonEnd < routes[i][0])
        {
            commonStart = routes[i][0];
            commonEnd = routes[i][1];

            // 카메라 추가
            answer++;
        }
        // 작을 경우
        else
        {
            commonStart = routes[i][0];
            commonEnd = min(routes[i][1], commonEnd);
        }
    }

    return answer;
}