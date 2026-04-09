using System.ComponentModel.DataAnnotations;
using System.Formats.Asn1;
using System.Net.Http.Headers;

namespace 백준10026번_적록색약
{
    class Program
    {
        // R = 1 
        // G = 2
        // B = 3
        public struct Pos
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
        static Pos[] dir = { new Pos(1, 0), new Pos(-1, 0), new Pos(0, 1), new Pos(0, -1) };

        // 1 = 적녹색약 (2,3) 확인
        // 0 = 일반 (1,2,3) 확인

        static int BFS(int n, int[,] map, int type)
        {
            int ret = 0;
            bool[,] visited = new bool[n, n];
            for (int y = 0; y < n; y++)
            {
                for (int x = 0; x < n; x++)
                {
                    if (visited[y, x] == true)
                        continue;
                    Queue<Pos> q = new Queue<Pos>();
                    q.Enqueue(new Pos(y, x));
                    while (q.Count > 0)
                    {
                        Pos cur = q.Dequeue();
                        for (int i = 0; i < 4; i++)
                        {
                            Pos next = cur + dir[i];
                            if (next.x < 0 || next.x >= n || next.y < 0 || next.y >= n)
                                continue;
                            if (visited[next.y, next.x] == true)
                                continue;
                            // 현재 탐색중인 영역이 아닌 경우
                            if (map[y, x] != map[next.y, next.x])
                            {
                                // 일반인일경우
                                if (type == 0)
                                    continue;
                                // 적록색약일 경우
                                else if (map[y, x] == 3 || map[next.y, next.x] == 3)
                                    continue;
                            }

                            visited[next.y, next.x] = true;
                            q.Enqueue(next);
                        }
                    }
                    ret++;
                }
            }

            return ret;
        }

        // BFS 탐색
        static int[] solution(int n, int[,] map)
        {
            return new int[] { BFS(n, map, 0), BFS(n, map, 1) };
        }

        static void Main(string[] argc)
        {
            int n = int.Parse(Console.ReadLine());

            int[,] map = new int[n, n];
            for (int i = 0; i < n; i++)
            {
                string row = Console.ReadLine();
                for (int j = 0; j < row.Length; j++)
                {
                    map[i, j] = row[j] == 'R' ? 1 : (row[j] == 'G' ? 2 : 3);
                }
            }
            int[] answer = solution(n, map);
            Console.WriteLine($"{answer[0]} {answer[1]}");
        }
    }
}