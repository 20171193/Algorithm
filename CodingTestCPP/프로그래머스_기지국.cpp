#include <iostream>
#include <vector>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;

    int coverBound = w * 2 + 1;

    int areaIndex = 0;
    // ������ ������ ���������� ���޵� ����
    int currentCity = 0;
    while (currentCity < n)
    {
        // �����ؾ��� ������ ����
        int targetCitys = 0;
        // ���̻� ���� ���ð� ���� ���
        if (areaIndex >= stations.size())
            targetCitys = n - currentCity;
        // ���� �ε������� ������ ��ȿ
        else if (currentCity < stations[areaIndex] - w)
            targetCitys = stations[areaIndex] - w - currentCity - 1;
        // ���� �ε����� Ȯ��
        else
            currentCity = stations[areaIndex] + w;

        // ���� Ž���������� ���� ���ð� �����Ѵٸ�
        if (targetCitys > 0)
        {
            int coverCount = targetCitys / coverBound;
            // ������ ���� ó��
            if (targetCitys % coverBound > 0)
                coverCount++;

            currentCity += targetCitys;
            answer += coverCount;
        }

        areaIndex++;
    }

    return answer;
}

int main()
{
    solution(11, { 4,11 }, 1);

    return 0;
}