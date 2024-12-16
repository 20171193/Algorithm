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

    // ����� �������� ���� �������� ����
    sort(routes.begin(), routes.end(), cmp);
    // ���� ���� ����
    int commonStart = routes[0][0];
    int commonEnd = routes[0][1];

    // ī�޶� ��� �� ��� ���� ����
    answer = 1;

    for (int i = 1; i < routes.size(); i++)
    {
        /// ���� ��� �������� ���� ��� �缳��
        // ����� ����� ������������ ���� ����� ���������� Ŭ ���
        if (commonEnd < routes[i][0])
        {
            commonStart = routes[i][0];
            commonEnd = routes[i][1];

            // ī�޶� �߰�
            answer++;
        }
        // ���� ���
        else
        {
            commonStart = routes[i][0];
            commonEnd = min(routes[i][1], commonEnd);
        }
    }

    return answer;
}