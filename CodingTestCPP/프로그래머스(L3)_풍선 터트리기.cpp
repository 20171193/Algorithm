#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> a) {
    int answer = 0;

    vector<int> leftMin(a.size()), rightMin(a.size());

    // ���� �ε��� ���� ���� �ּҰ� �Ҵ�
    leftMin[0] = a[0];
    for (int i = 1; i < a.size(); i++)
        leftMin[i] = min(leftMin[i - 1], a[i]);


    // ���� �ε��� ���� ������ �ּҰ� �Ҵ�
    rightMin[a.size() - 1] = a[a.size() - 1];
    for (int i = a.size() - 2; i >= 0; i--)
        rightMin[i] = min(rightMin[i + 1], a[i]);

    // ������ �ּҰ� ��� ���� �ε������� �۴ٸ� �����Ұ�
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] <= leftMin[i] || a[i] <= rightMin[i])
            answer++;
    }

    return answer;
}