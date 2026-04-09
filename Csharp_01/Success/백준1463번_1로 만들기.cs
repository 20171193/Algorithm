using System;
using System.ComponentModel.Design;
using System.Data;
using System.Numerics;
using System.Runtime.CompilerServices;

namespace 백준1463번_1로_만들기
{
    class Program
    {
        // params 써보고싶어서 써봄
        static int IMin(params int[] values)
        {
            int ret = int.MaxValue;
            for (int i = 0; i < values.Length; i++)
            {
                ret = Math.Min(ret, values[i]);
            }
            return ret;
        }

        static int solution(int n)
        {
            int answer = 0;
            int[] dp = new int[1000001];
            dp[0] = 0;
            dp[1] = 1;
            for (int i = 2; i <= n; i++)
            {
                // 3과 2의 최소 공배수도 고려해야함.
                if (i % 6 == 0)
                    dp[i] = IMin(dp[i / 3], dp[i / 2], dp[i - 1]) + 1;
                else if (i % 3 == 0)
                    dp[i] = IMin(dp[i / 3], dp[i - 1]) + 1;
                else if (i % 2 == 0)
                    dp[i] = IMin(dp[i / 2], dp[i - 1]) + 1;
                else
                    dp[i] = dp[i - 1] + 1;
            }
            answer = dp[n];
            return answer - 1;
        }
        static void Main()
        {
            Console.WriteLine(solution(int.Parse(Console.ReadLine())));
        }
    }
}