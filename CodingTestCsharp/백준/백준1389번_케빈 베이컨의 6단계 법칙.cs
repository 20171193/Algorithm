using System;

namespace 백준1389번_케빈_베이컨의_6단계_법칙
{
    class Program
    {
        // BFS
        static int BFS(int n, List<int>[] edges)
        {
            int ret = -1;
            int minKebin = int.MaxValue;
            for (int start = 1; start <= n; start++)
            {
                int curKebin = 0;
                int[] visited = new int[n + 1];
                Queue<int> q = new Queue<int>();
                visited[start] = 1;
                q.Enqueue(start);
                while (q.Count > 0)
                {
                    int cur = q.Dequeue();
                    for (int i = 0; i < edges[cur].Count; i++)
                    {
                        int next = edges[cur][i];

                        if (visited[next] > 0)
                        {
                            if (visited[next] > visited[cur] + 1)
                                visited[next] = visited[cur] + 1;
                            continue;
                        }

                        visited[next] = visited[cur] + 1;
                        q.Enqueue(next);
                    }
                }

                for (int i = 1; i < visited.Length; i++)
                    curKebin += visited[i];

                if (curKebin < minKebin)
                {
                    minKebin = curKebin;
                    ret = start;
                }
            }

            return ret;
        }

        static void Main(string[] args)
        {
            string[] nm = Console.ReadLine().Split(' ');

            int n = int.Parse(nm[0]);
            int m = int.Parse(nm[1]);

            List<int>[] edges = new List<int>[n + 1];
            for (int i = 0; i < m; i++)
            {
                string[] se = Console.ReadLine().Split(' ');
                int s = int.Parse(se[0]);
                int e = int.Parse(se[1]);

                if (edges[s] == null)
                    edges[s] = new List<int>();
                edges[s].Add(e);
                if (edges[e] == null)
                    edges[e] = new List<int>();
                edges[e].Add(s);
            }

            Console.WriteLine(BFS(n, edges));
        }
    }
}