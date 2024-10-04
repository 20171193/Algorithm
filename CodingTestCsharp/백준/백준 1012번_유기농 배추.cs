// 백준 1012번 유기농 배추
using System;
using System.Numerics;

// 지렁이는 인접한 다른 배추로 이동
// 배추가 심어져있는 영역 구하기
// 영역 -> BFS

class Program
{
    struct Pos
    {
        public int x = 0;
        public int y = 0;
        public Pos(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
        public static Pos operator +(Pos p1, Pos p2)
        {
            return new Pos(p1.x + p2.x, p1.y + p2.y);
        }
    }
    static Pos[] dir = { new Pos(1, 0), new Pos(-1, 0), new Pos(0, 1), new Pos(0, -1) };

    static void BFS(int[,] map, bool[,] visited, int y, int x)
    {
        visited[y, x] = true;
        Queue<Pos> q = new Queue<Pos>();
        q.Enqueue(new Pos(x, y));

        while (q.Count > 0)
        {
            Pos cur = q.Dequeue();
            for (int i = 0; i < 4; i++)
            {
                Pos next = cur + dir[i];
                if (next.x < 0 || next.x >= visited.GetLength(1)
                    || next.y < 0 || next.y >= visited.GetLength(0))
                    continue;
                if (visited[next.y, next.x])
                    continue;
                if (map[next.y, next.x] != 1)
                    continue;

                visited[next.y, next.x] = true;
                q.Enqueue(next);
            }
        }
    }

    static int solution(int m, int n, int k, int[,] map)
    {
        int answer = 0;

        bool[,] visited = new bool[n, m];
        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < m; x++)
            {
                if (visited[y, x] == true) continue;
                if (map[y, x] != 1) continue;

                BFS(map, visited, y, x);
                answer++;
            }
        }

        return answer;
    }
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            string[] mnk = Console.ReadLine().Split();
            int m = int.Parse(mnk[0]);
            int n = int.Parse(mnk[1]);
            int k = int.Parse(mnk[2]);

            int[,] map = new int[n, m];

            for (int i = 0; i < k; i++)
            {
                string[] xy = Console.ReadLine().Split();
                int x = int.Parse(xy[0]);
                int y = int.Parse(xy[1]);
                map[y, x] = 1;
            }
            Console.WriteLine(solution(m, n, k, map));
        }
    }
}