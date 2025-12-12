using System;
using System.Numerics;
using System.Reflection.Metadata.Ecma335;
using System.Reflection.PortableExecutable;
using System.Text;

namespace CodingTestCsharp.백준
{
    // 백준 23081번 : 오델로 (https://www.acmicpc.net/problem/23081)
    // 조건
    // 1. 8방향에 돌을 놓을 수 있음.
    // 2. 가장 많은 백돌을 뒤집을 수 있는 곳.
    // 풀이
    // 1. 빈칸에서 8방향 탐색
    class 백준23081번_오델로
    {
        static int n;
        static string[] board;
        public struct Pos
        {
            public readonly int y;
            public readonly int x;
            public Pos(int y, int x) { this.y = y; this.x = x; }

            public static readonly Pos[] directions = { new Pos(-1, -1), new Pos(0, -1), new Pos(1, -1), new Pos(1, 0), new Pos(-1, 0), new Pos(-1, 1), new Pos(0, 1), new Pos(1, 1) };

            public bool CheckBound(int maxBound) { return y >= 0 && y < maxBound && x >= 0 && x < maxBound; }
            public static Pos operator +(Pos a, Pos b)
            {
                return new Pos(a.y + b.y, a.x + b.x);
            }
        }

        // 방향 탐색 (백돌 카운팅)
        static int CheckDirection(Pos start, int dir)
        {
            int cnt = 0;
            Pos cur = start;
            while (true)
            {
                if (!cur.CheckBound(n)) return 0;
                if (board[cur.y][cur.x] == '.') return 0;
                if (board[cur.y][cur.x] == 'B') return cnt;

                cnt++;
                cur = cur + Pos.directions[dir];
            }
        }

        static void solution()
        {
            Pos resultPos = new Pos(-1, -1);
            int resultCount = -1;

            for (int y = 0; y < n; y++)
            {
                for (int x = 0; x < n; x++)
                {
                    if (board[y][x] != '.') continue;

                    int cnt = 0;
                    Pos cur = new Pos(y, x);
                    for (int d = 0; d < 8; d++)
                    {
                        Pos next = cur + Pos.directions[d];
                        if (!next.CheckBound(n)) continue;
                        if (board[next.y][next.x] != 'W') continue;
                        cnt += CheckDirection(next, d);
                    }

                    if (resultCount < cnt)
                    {
                        resultCount = cnt;
                        resultPos = cur;
                    }
                }
            }

            if (resultCount <= 0)
                Console.WriteLine("PASS");
            else
                Console.WriteLine($"{resultPos.x} {resultPos.y}\n{resultCount}");
        }

        static void Main(string[] args)
        {
            n = int.Parse(Console.ReadLine());
            board = new string[n];
            for (int i = 0; i < n; i++)
                board[i] = Console.ReadLine();

            solution();
        }
    }
}
