using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodingTestCsharp.백준
{
    internal class 백준_12865번_평범한_배낭
    {
        public struct OBJ
        {
            public int w;
            public int v;
            public OBJ(int w, int v)
            {
                this.w = w;
                this.v = v;
            }
        }

        static int n = 0, k = 0;
        static List<OBJ> objects = new List<OBJ>();

        public static void Main()
        {
            string[] temp = Console.ReadLine().Split(' ');
            n = int.Parse(temp[0]);
            k = int.Parse(temp[1]);
            for (int i = 0; i < n; i++)
            {
                temp = Console.ReadLine().Split(' ');
                objects.Add(new OBJ(int.Parse(temp[0]), int.Parse(temp[1])));
            }
            int[,] dp = new int[n + 1, k + 1];
            // dp[i, j] : i 개수 물건을 고려했을 때 최대 가치
            // dp[1, 6] = dp[1, 7] = 13
            // dp[2, 6] = dp[2, 7] = 13 
            // dp[3, 7] = dp[]


            for (int i = 1; i <= n; i++)
            {
                for (int j = 0; j <= k; j++)
                {
                    if (objects[i - 1].w <= j)
                    {
                        dp[i, j] =
                            Math.Max(dp[i - 1, j], dp[i - 1, j - objects[i - 1].w] + objects[i - 1].v);
                    }
                    else
                    {
                        dp[i, j] = dp[i - 1, j];
                    }
                }
            }

            Console.WriteLine(dp[n, k]);
        }
    }
}

