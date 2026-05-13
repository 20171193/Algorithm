// 프로그래머스(L4) : 징검다리
// 조건
// 1. 0~distance사이의 바위의 위치가 주어짐(0, distance에도 존재)
// 2. n개의 바위를 제거한 뒤 각 지점 사이의 거리의 최솟값 중 가장 큰 값을 리턴
// 풀이
// 1. 모든 경우의 수 조합(50,000cN)은 불가
// 2. 이분 탐색
//  2-1. 0~distance 사이에서 '간격'기준 탐색
//  2-2. mid 간격 미만의 돌을 모두 제거한 개수 구하기
//  2-3. 해당 개수가 n 이하라면 가능. (최솟값 갱신) => 최솟값 중 가장 큰 값을 구해야 함.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;

public class Solution
{
    // diff 간격 미만의 돌을 제거
    public static int RemoveCount(int[] rocks, int distance, int diff)
    {
        int prev = 0, count = 0;
        foreach (int cur in rocks)
        {
            if (cur - prev < diff) count++;    // 제거
            else prev = cur;    // 살리고 갱신
        }

        // 마지막 구간 체크
        if (distance - prev < diff)
            count++;

        return count;
    }

    public int solution(int distance, int[] rocks, int n)
    {
        int answer = 0;

        Array.Sort(rocks);
        int left = 0, right = distance, removedCnt = 0;
        while (left <= right)
        {
            int mid = (left + right) >> 1;
            removedCnt = RemoveCount(rocks, distance, mid);

            if (removedCnt <= n)
            {
                answer = mid;
                left = mid + 1;
            }
            else
                right = mid - 1;
        }

        return answer;
    }

}
