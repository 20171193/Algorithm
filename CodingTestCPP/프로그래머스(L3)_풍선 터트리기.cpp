#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> a) {
    int answer = 0;

    vector<int> leftMin(a.size()), rightMin(a.size());

    // 현재 인덱스 기준 왼쪽 최소값 할당
    leftMin[0] = a[0];
    for (int i = 1; i < a.size(); i++)
        leftMin[i] = min(leftMin[i - 1], a[i]);


    // 현재 인덱스 기준 오른쪽 최소값 할당
    rightMin[a.size() - 1] = a[a.size() - 1];
    for (int i = a.size() - 2; i >= 0; i--)
        rightMin[i] = min(rightMin[i + 1], a[i]);

    // 양쪽의 최소값 모두 현재 인덱스보다 작다면 생존불가
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] <= leftMin[i] || a[i] <= rightMin[i])
            answer++;
    }

    return answer;
}