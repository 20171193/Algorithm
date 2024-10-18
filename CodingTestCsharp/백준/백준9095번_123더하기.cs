using System;
using System.Text;

namespace 백준9095번_123더하기
{
    class Program
    {
        static Func<int, int>[] oper = new Func<int, int>[]
        {
            (value) => value+1,
            (value) => value+2,
            (value) => value+3
        };

        // BFS 풀이
        static int solutionBFS(int n)
        {
            Queue<int> q = new Queue<int>();
            q.Enqueue(0);
            int[] count = new int[11];
            count[0] = 1;
            while (q.Count > 0)
            {
                int cur = q.Dequeue();
                for (int i = 0; i < 3; i++)
                {
                    int next = oper[i](cur);
                    if (next > n) continue;

                    if (count[next] != 0)
                    {
                        count[next] += count[cur];
                        continue;
                    }
                    count[next] += count[cur];
                    q.Enqueue(next);
                }
            }

            return count[n];
        }

        // DP 풀이
        static int[] dp = new int[11];
        static int solutionDP(int n)
        {
            if (dp[n] > 0)
                return dp[n];

            dp[0] = 0;
            dp[1] = 1;
            dp[2] = 2;  // 1 1, 2
            dp[3] = 4; // 1 1 1, 2 1, 1 2, 3
            // dp[4] -> 3+1, 2+2, 1+3
            // dp[n] = dp[n-1] + dp[n-2] + dp[n-3];

            for (int i = 4; i < 11; i++)
            {
                dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
            }
            return dp[n];
        }

        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine());
            while (t-- > 0)
            {
                int n = int.Parse(Console.ReadLine());
                Console.WriteLine(solutionBFS(n));
            }
        }
    }
}