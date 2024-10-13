using System.ComponentModel;

namespace 백준7576번_토마토
{
    class Program
    {
        struct Pos
        {
            public int x, y;
            public static Pos operator +(Pos p1, Pos p2)
            {
                return new Pos(p1.x + p2.x, p1.y + p2.y);
            }
            public Pos(int x, int y)
            {
                this.x = x;
                this.y = y;
            }
        }

        static int solution(int m, int n, int[,] box)
        {
            int answer = -1;
            Pos[] dir =
                {
                new Pos(1,0),
                new Pos(-1,0),
                new Pos(0,1),
                new Pos(0,-1)
            };
            Queue<Pos> q = new Queue<Pos>();
            for (int y = 0; y < n; y++)
            {
                for (int x = 0; x < m; x++)
                {
                    if (box[y, x] == 1)
                    {
                        q.Enqueue(new Pos(x, y));
                    }
                }
            }

            while (q.Count > 0)
            {
                Pos cur = q.Dequeue();
                for (int i = 0; i < 4; i++)
                {
                    Pos next = cur + dir[i];
                    if (next.x < 0 || next.x >= m) continue;
                    if (next.y < 0 || next.y >= n) continue;
                    if (box[next.y, next.x] == -1) continue;
                    if (box[next.y, next.x] > 0)
                    {
                        box[next.y, next.x] = Math.Min(box[next.y, next.x], box[cur.y, cur.x] + 1);
                        continue;
                    }
                    box[next.y, next.x] = box[cur.y, cur.x] + 1;
                    q.Enqueue(next);
                }
            }
            for (int y = 0; y < n; y++)
            {
                for (int x = 0; x < m; x++)
                {
                    if (box[y, x] == 0)
                        return -1;

                    answer = Math.Max(answer, box[y, x]);
                }
            }

            return answer - 1;
        }

        static void Main(string[] args)
        {
            int[] mn = Console.ReadLine().Split(" ").Select(int.Parse).ToArray();

            int[,] arr = new int[mn[1], mn[0]];
            for (int y = 0; y < mn[1]; y++)
            {
                int[] temp = Console.ReadLine().Split(" ").Select(int.Parse).ToArray();
                for (int x = 0; x < mn[0]; x++)
                {
                    arr[y, x] = temp[x];
                }
            }
            Console.WriteLine(solution(mn[0], mn[1], arr));
        }
    }

}