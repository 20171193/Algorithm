using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace CodingTestCsharp.백준
{
    // 백준17244번 : 아맞다우산(https://www.acmicpc.net/problem/17244)
    // 1. m, n
    // 2. S-E 경로 중 X를 모두 경유하는 최소 시간
    class 백준17244번_아맞다우산
    {
        public struct Pos
        {
            public int y, x;
            public Pos(int y, int x) { this.y = y; this.x = x; }
            public static Pos operator +(Pos a, Pos b)
            {
                return new Pos(a.y + b.y, a.x + b.x);
            }
            public static bool operator ==(Pos a, Pos b)
            {
                return a.y == b.y && a.x == b.x;
            }
            public static bool operator !=(Pos a, Pos b)
            {
                return a.y != b.y || a.x != b.x;
            }
        }
        static Pos[] directions = { new Pos(1, 0), new Pos(-1, 0), new Pos(0, 1), new Pos(0, -1) };
        public struct State
        {
            public Pos pos;
            public int bit;
            public int y { get { return pos.y; } }
            public int x { get { return pos.x; } }
            public State(Pos pos, int bit) { this.pos = pos; this.bit = bit; }
        }

        static int solution(int m, int n, char[,] map)
        {
            int answer = int.MaxValue;
            Queue<State> q = new Queue<State>();
            // 물건 리스트(최대 5개) - 비트마스킹
            List<Pos> objs = new List<Pos>();
            // 출구
            Pos exit = new Pos();
            Pos start = new Pos();
            // 조건 포맷
            for (int y = 0; y < m; y++)
            {
                for (int x = 0; x < n; x++)
                {
                    if (map[y, x] == 'S')
                        start = new Pos(y, x);
                    else if (map[y, x] == 'X')
                        objs.Add(new Pos(y, x));
                    else if (map[y, x] == 'E')
                        exit = new Pos(y, x);
                }
            }

            int[,,] visited = new int[m, n, (1 << objs.Count)];

            q.Enqueue(new State(start, 0));
            visited[start.y, start.x, 0] = 1;

            while (q.Count > 0)
            {
                State cur = q.Dequeue();
                // 가지치기
                if (answer > 0 && answer < visited[cur.y, cur.x, cur.bit])
                    continue;

                // 탈출조건
                if (exit == cur.pos && cur.bit == (1 << objs.Count) - 1)
                {
                    answer = Math.Min(answer, visited[cur.y, cur.x, (1 << objs.Count) - 1]);
                    break;
                }

                for (int d = 0; d < 4; d++)
                {
                    Pos next = cur.pos + directions[d];
                    if (next.y < 0 || next.y >= m || next.x < 0 || next.x >= n)
                        continue;
                    if (map[next.y, next.x] == '#')
                        continue;

                    int nBit = cur.bit;
                    if (map[next.y, next.x] == 'X')
                    {
                        for (int b = 0; b < objs.Count; b++)
                        {
                            if (objs[b] == next)
                            {
                                if ((cur.bit & (1 << b)) == 0)
                                {
                                    nBit |= (1 << b);
                                }
                                break;
                            }
                        }
                    }
                    int nVisit = visited[cur.y, cur.x, cur.bit] + 1;
                    if (cur.bit == nBit && visited[next.y, next.x, cur.bit] > 0 && visited[next.y, next.x, cur.bit] <= nVisit)
                        continue;

                    visited[next.y, next.x, nBit] = nVisit;
                    q.Enqueue(new State(next, nBit));
                }
            }
            return answer - 1;
        }
        static void Main(string[] args)
        {
            string[] temp = Console.ReadLine().Split(' ');
            int n = int.Parse(temp[0]);
            int m = int.Parse(temp[1]);
            char[,] map = new char[m, n];
            for (int y = 0; y < m; y++)
            {
                string str = Console.ReadLine();
                for (int x = 0; x < n; x++)
                {
                    map[y, x] = str[x];
                }
            }
            Console.WriteLine(solution(m, n, map));
        }
    }
}

