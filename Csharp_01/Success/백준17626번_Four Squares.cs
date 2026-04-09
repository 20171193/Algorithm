using System;
using System.Collections;

namespace 백준17626번_Four_Squares
{
    class Program
    {
        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());

            int[] dp = new int[n + 1];

            dp[0] = 0;
            for (int i = 1; i <= n; i++)
            {
                dp[i] = int.MaxValue;
                for (int j = 1; j * j <= i; j++)
                {
                    dp[i] = Math.Min(dp[i], dp[i - j * j] + 1);
                }
            }

            Console.WriteLine(dp[n]);
        }
    }
}