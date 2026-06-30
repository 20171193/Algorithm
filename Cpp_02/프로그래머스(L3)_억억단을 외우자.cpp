// 프로그래머스(L3) : 억억단을 외우자
// 문제
// 1. 억억단 : 1억*1억 크기의 행렬
// 2. s~e 범위에서 가장 많이 등장한 수를 답해야 함.
//    (등장 횟수가 같다면 더 작은 수)
// 조건
// 1. 1 <= e <= 5,000,000
// 2. s배열 starts : 1 <= starts.size() <= min(e, 100,000)
// 풀이
// 1. r*c 쌍의 개수 => 곧 약수의 개수
//    => 2~e 까지 약수 개수 미리 할당
// 2. 쿼리 : e~최솟값까지 갱신
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(int e, vector<int> starts) {
    vector<int> answer(starts.size());

    // 약수 개수
    vector<int> factCount(e + 1);
    for (int i = 2; i  <= e; i++)
        for (int j = i; j <= e; j += i)
            factCount[j]++;

    // 쿼리(작은 수로 갱신)
    vector<int> query(e + 1);
    query[e] = e;

    int mn = *min_element(starts.begin(), starts.end());
    for (int i = e-1; i >= mn; i--) {
        if (factCount[query[i + 1]] <= factCount[i]) query[i] = i;
        else query[i] = query[i + 1];
    }

    for (int i = 0; i < starts.size(); i++)
        answer[i] = query[starts[i]];

    return answer;
}
