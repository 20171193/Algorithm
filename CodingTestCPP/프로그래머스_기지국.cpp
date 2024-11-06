#include <iostream>
#include <vector>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;

    int coverBound = w * 2 + 1;

    int areaIndex = 0;
    // 기지국 증설로 마지막으로 전달된 도시
    int currentCity = 0;
    while (currentCity < n)
    {
        // 전달해야할 도시의 개수
        int targetCitys = 0;
        // 더이상 덮인 도시가 없을 경우
        if (areaIndex >= stations.size())
            targetCitys = n - currentCity;
        // 현재 인덱스에서 범위가 유효
        else if (currentCity < stations[areaIndex] - w)
            targetCitys = stations[areaIndex] - w - currentCity - 1;
        // 다음 인덱스를 확인
        else
            currentCity = stations[areaIndex] + w;

        // 현재 탐색범위에서 덮을 도시가 존재한다면
        if (targetCitys > 0)
        {
            int coverCount = targetCitys / coverBound;
            // 나머지 영역 처리
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