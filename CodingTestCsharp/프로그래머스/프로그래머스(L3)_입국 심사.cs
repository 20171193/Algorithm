using System;
using System.Linq;

namespace 프로그래머스_L3_입국_심사
{
    public class Solution
    {
        static bool Check(int n, long m, int[] times)
        {
            long cnt = 0;
            for (int i = 0; i < times.Length; i++)
            {
                cnt += m / times[i];
                if (cnt >= n)
                    return true;
            }

            return false;
        }

        static long solution(int n, int[] times)
        {
            long answer = 0;

            long left = 1, right = 1000000000;
            long mid = 0;
            while (left <= right)
            {
                mid = (left + right) >> 1;

                if (Check(n, mid, times))
                    right = mid - 1;
                else
                    left = mid + 1;
            }

            answer = left;

            return answer;
        }

        static void Main(string[] args)
        {
            Console.WriteLine(solution(6, new int[2] { 7, 10 }));
        }
    }
}