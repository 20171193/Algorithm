using System;
using System.Numerics;

namespace 백준2638번_치즈
{
    class Program
    {
        public struct Pos
        {
            public int x;
            public int y;
            public Pos(int x, int y) { this.x = x; this.y = y; }
            public static Pos operator +(Pos a, Pos b)
            {
                return new Pos(a.x + b.x, a.y + b.y);
            }
        }
        static int Solve(int n, int m, int[,] map)
        {
            int time = 0;
            Pos[] dir = {
                new Pos(1, 0),
                new Pos(-1, 0),
                new Pos(0, 1),
                new Pos(0, -1) };

            int[,] visited = new int[n, m];
            Queue<Pos> q = new Queue<Pos>();

            int cheeseCount = 0;
            do
            {
                cheeseCount = 0;
                q.Enqueue(new Pos(0, 0));   // 맨 가장자리는 치즈가 놓이지 않음.
                visited[0, 0] = -1;

                while (q.Count > 0)
                {
                    Pos cur = q.Dequeue();

                    for (int i = 0; i < 4; i++)
                    {
                        Pos next = cur + dir[i];

                        // 범위 체크
                        if (next.x < 0 || next.x >= m || next.y < 0 || next.y >= n)
                            continue;
                        // 방문 체크
                        if (visited[next.y, next.x] == -1)
                            continue;

                        // 치즈 발견 시 
                        if (map[next.y, next.x] == 1)
                        {
                            if (visited[next.y, next.x] == 1)
                            {
                                map[next.y, next.x] = 0;
                                visited[next.y, next.x] = -1;
                            }
                            else
                            {
                                visited[next.y, next.x] = 1;
                                cheeseCount++;
                            }
                        }
                        else
                        {
                            visited[next.y, next.x] = -1;
                            q.Enqueue(next);
                        }
                    }
                }

                // 방문 배열 초기화
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < m; j++)
                        visited[i, j] = 0;

                time++;
            }
            while (cheeseCount > 0);

            // 마지막 탐색은 남은 치즈 확인용
            return time - 1;
        }

        static void Main(string[] args)
        {
            string[] nm = Console.ReadLine().Split(' ');

            int n = int.Parse(nm[0]);
            int m = int.Parse(nm[1]);

            int[,] map = new int[n, m];
            int idx = 0;
            for (int i = 0; i < n; i++)
            {
                string str = Console.ReadLine();
                for (int j = 0; j < str.Length; j += 2)
                {
                    map[i, idx++] = str[j] - '0';
                }
                idx = 0;
            }
            Console.WriteLine(Solve(n, m, map));
        }
    }
}