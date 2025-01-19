using System;
using System.Collections;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Text;

namespace 백준16236번_아기_상어
{
    class Program
    {
        public struct Pos
        {
            public int x;
            public int y;
            public Pos(int y, int x)
            {
                this.y = y;
                this.x = x;
            }
            public static Pos operator +(Pos a, Pos b)
            {
                return new Pos(a.y + b.y, a.x + b.x);
            }
        }

        static int N;
        static int[,] map;
        static Pos[] dir = { new Pos(-1, 0), new Pos(0, -1), new Pos(1, 0), new Pos(0, 1) };

        // 이동은 1초
        // 이동의 우선 순위는 아래 > 왼쪽 > 위 = 오른쪽
        // 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기 1증가
        static bool Find(Pos startPos, int curSize, out Pos findPos, out int dist)
        {
            int[,] visited = new int[N, N];
            Queue<Pos> q = new Queue<Pos>();

            visited[startPos.y, startPos.x] = 1;
            q.Enqueue(startPos);

            while (q.Count > 0)
            {
                Pos curPos = q.Dequeue();
                for (int i = 0; i < 4; i++)
                {
                    Pos nextPos = curPos + dir[i];
                    if (nextPos.x < 0 || nextPos.x >= N || nextPos.y < 0 || nextPos.y >= N)
                        continue;
                    if (map[nextPos.y, nextPos.x] > curSize)
                        continue;

                    // 크기가 작은 물고기를 찾은 경우
                    if (map[nextPos.y, nextPos.x] > 0 && map[nextPos.y, nextPos.x] < curSize)
                    {
                        // 시작지점을 1로 할당
                        dist = visited[curPos.y, curPos.x];
                        findPos = nextPos;
                        return true;
                    }

                    // 이미 방문한 영역은 거리 갱신
                    if (visited[nextPos.y, nextPos.x] > 0)
                    {
                        visited[nextPos.y, nextPos.x] = Math.Min(visited[nextPos.y, nextPos.x], visited[curPos.y, curPos.x] + 1);
                        continue;
                    }

                    visited[nextPos.y, nextPos.x] = visited[curPos.y, curPos.x] + 1;
                    q.Enqueue(nextPos);
                }
            }
            findPos = new Pos(-1, -1);
            dist = -1;
            return false;
        }
        static int solution(Pos start)
        {
            int ret = 0, curSize = 2, eatCount = 0;

            Pos curPos = start;
            while (Find(curPos, curSize, out Pos getPos, out int getDist))
            {
                // 먹은 위치는 0 할당
                map[getPos.y, getPos.x] = 0;

                eatCount++;
                if (eatCount == curSize)
                {
                    curSize += 1;
                    eatCount = 0;
                }

                ret += getDist;
                curPos = getPos;
            }

            return ret;
        }
        static void Main(string[] args)
        {
            // input
            N = int.Parse(Console.ReadLine());
            map = new int[N, N];
            Pos startPos = new Pos(-1, -1);

            for (int y = 0; y < N; y++)
            {
                string[] temp = Console.ReadLine().Split(' ');
                for (int x = 0; x < N; x++)
                {
                    map[y, x] = int.Parse(temp[x]);
                    if (map[y, x] == 9)
                    {
                        startPos = new Pos(y, x);
                        map[y, x] = 0;
                    }
                }
            }

            // output
            Console.WriteLine(solution(startPos));
        }
    }
}