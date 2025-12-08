using System;
using System.Text;

namespace CodingTestCsharp.백준
{
    // 백준1014번 : 컨닝(https://www.acmicpc.net/problem/1014)
    // 1. 10*10
    // 2. 전체 조합(2^100) 불가
    // 3. 행마다 비트마스킹 + 메모이제이션
    // 4. 좌우, 대각 비교
    class Program
    {
        static int solution(int n, int m, string[] room)
        {
            int[,] dp = new int[n, (1 << m)];   // 1-based row

            int totalCount = 0;
            for (int row = 0; row < n; row++)
            {
                for (int mask = 0; mask < (1 << m); mask++)
                {
                    // 좌/우 확인
                    if ((mask & (mask << 1)) != 0) continue;

                    bool validFlag = true;
                    int cnt = 0;
                    for (int col = 0; col < m; col++)
                    {
                        if ((mask & (1 << col)) == 0) continue;
                        if (room[row][col] == 'x')
                        {
                            validFlag = false;
                            break;
                        }

                        cnt++;
                    }

                    // 현재 마스크가 가능한 마스크인지
                    if (!validFlag) continue;

                    // 0행 처리
                    if (row == 0)
                        dp[row, mask] = cnt;
                    else // row > 0
                    {
                        // 이전 마스크와 비교
                        for (int prevMask = 0; prevMask < (1 << m); prevMask++)
                        {
                            // 대각 확인
                            if ((mask & (prevMask << 1)) != 0 || (mask & (prevMask >> 1)) != 0) continue;

                            dp[row, mask] = Math.Max(dp[row, mask], dp[row - 1, prevMask] + cnt);
                        }
                    }

                    totalCount = Math.Max(totalCount, dp[row, mask]);
                }
            }
            return totalCount;
        }


        static void Main(string[] args)
        {
            // input
            int c = int.Parse(Console.ReadLine());
            StringBuilder stbd = new StringBuilder();
            while (c-- > 0)
            {
                string[] nm = Console.ReadLine().Split(' ');
                int n = int.Parse(nm[0]);
                int m = int.Parse(nm[1]);

                string[] room = new string[n];
                for (int i = 0; i < n; i++)
                    room[i] = Console.ReadLine();

                // solve
                stbd.AppendLine($"{solution(n, m, room)}");
            }

            // output
            Console.WriteLine(stbd.ToString());
        }
    }
}
