using System;
using System.Collections.Generic;

// 백준 1092번 : 배
// 조건
// 1. 크레인 N(1<=N<=50) 대
// 2. 1분에 박스를 하나씩 실을 수 있고, 모든 크레인은 동시에 움직임
// 3. 박스 M(1<=M<=10,000), 무게 최대 1,000,000
// 4. 모든 박스를 옮기는 데 드는 시간의 최솟값 출력
// 풀이
// 1. 그리디 + 인덱스 메모이제이션
class 백준1092번_배
{
    static int n, m;
    static int[] cranes, boxes;

    static int Solution()
    {
        Array.Sort(cranes, (a, b) => b.CompareTo(a));
        Array.Sort(boxes, (a, b) => b.CompareTo(a));

        if (cranes[0] < boxes[0]) return -1;


        int remain = m, time = 0;
        bool[] carried = new bool[m];
        int[] craneIndexes = new int[n];    // 크레인 별 탐색시작 인덱스

        while (remain > 0)
        {
            for (int i = 0; i < n; i++)
            {
                bool carriedFlag = false;
                for (int j = craneIndexes[i]; j < m; j++)
                {
                    if (carried[j]) continue;

                    if (cranes[i] >= boxes[j])
                    {
                        carried[j] = true;
                        remain--;
                        craneIndexes[i] = j + 1;
                        carriedFlag = true;
                        break;
                    }
                }

                if (!carriedFlag)
                    break;
            }

            time++;
        }

        return time;
    }
}