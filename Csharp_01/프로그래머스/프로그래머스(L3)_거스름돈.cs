using System;
using System.ComponentModel.Design;
using System.Globalization;
using System.Numerics;

namespace 프로그래머스L3_거스름돈
{
    class Program
    {
        static int solution(int n, int[] money)
        {
            int[] dp = new int[n + 1];

            Array.Sort(money);

            for (int i = 0; i < money.Length; i++)
            {
                for (int j = money[i]; j <= n; j++)
                {
                    dp[j] += dp[j - money[i]];
                }
            }

            return dp[n];
        }
    }
}