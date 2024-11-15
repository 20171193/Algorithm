using System;
using System.Data;
using System.Numerics;
using System.Reflection.Metadata.Ecma335;
namespace 백준2206번_벽_부수고_이동하기
{
    class Program
    {
        struct Pos
        {
            public int x;
            public int y;
            public Pos(int y, int x)
            {
                this.x = x;
                this.y = y;
            }
            public static Pos operator +(Pos a, Pos b)
            {
                return new Pos(a.y + b.y, a.x + b.x);
            }
        }
        struct Path
        {
            public Pos pos;
            public int isUsed;
            public Path(Pos pos, int isUsed)
            {
                this.pos = pos;
                this.isUsed = isUsed;
            }
        }
        static int n, m;
        static int[,] arr;
        static int[,,] visited;
        static Pos[] dir = { new Pos(1, 0), new Pos(-1, 0), new Pos(0, -1), new Pos(0, 1) };
        static int BFS()
        {
            int ret = int.MaxValue;
            Queue<Path> q = new Queue<Path>();
            visited[0, 0, 0] = visited[0, 0, 1] = 1;
            q.Enqueue(new Path(new Pos(0, 0), 0));

            while (q.Count > 0)
            {
                Path cur = q.Dequeue();

                if (cur.pos.y == n - 1 && cur.pos.x == m - 1)
                {
                    ret = Math.Min(visited[cur.pos.y, cur.pos.x, cur.isUsed], ret);
                    continue;
                }

                for (int i = 0; i < 4; i++)
                {
                    Pos next = cur.pos + dir[i];

                    // 범위 체크
                    if (next.x < 0 || next.x >= m || next.y < 0 || next.y >= n)
                        continue;
                    // 벽 확인
                    if (arr[next.y, next.x] == 1)
                    {
                        if (cur.isUsed == 1)
                            continue;
                        if (visited[next.y, next.x, 1] > 0)
                        {
                            visited[next.y, next.x, 1]
                                = Math.Min(visited[cur.pos.y, cur.pos.x, 0] + 1
                                , visited[next.y, next.x, 1]);
                            continue;
                        }

                        visited[next.y, next.x, 1] = visited[cur.pos.y, cur.pos.x, 0] + 1;
                        q.Enqueue(new Path(next, 1));
                    }
                    else
                    {
                        if (visited[next.y, next.x, cur.isUsed] > 0)
                        {
                            visited[next.y, next.x, cur.isUsed]
                                = Math.Min(visited[cur.pos.y, cur.pos.x, cur.isUsed] + 1
                                , visited[next.y, next.x, cur.isUsed]);
                            continue;
                        }

                        visited[next.y, next.x, cur.isUsed] = visited[cur.pos.y, cur.pos.x, cur.isUsed] + 1;
                        q.Enqueue(new Path(next, cur.isUsed));
                    }
                }
            }

            return ret == int.MaxValue ? -1 : ret;
        }

        static void Main(string[] argc)
        {
            string[] nm = Console.ReadLine().Split(' ');
            n = int.Parse(nm[0]);
            m = int.Parse(nm[1]);

            arr = new int[n, m];
            visited = new int[n, m, 2];

            for (int i = 0; i < n; i++)
            {
                string temp = Console.ReadLine();
                for (int j = 0; j < m; j++)
                    arr[i, j] = temp[j] - '0';
            }

            Console.WriteLine(BFS());
        }
    }
}