using System;

namespace 백준13549번_숨바꼭질_3
{
    class Program
    {
        static Func<int, int>[] oper =
        {
            pos => pos + 1,
            pos => pos - 1,
            pos => pos*2
        };

        static int BFS(int n, int k)
        {
            int[] visited = new int[200001];
            Queue<int> q = new Queue<int>();
            q.Enqueue(n);
            visited[n] = 1;
            while (q.Count > 0)
            {
                int cur = q.Dequeue();

                for (int i = 0; i < 3; i++)
                {
                    int next = oper[i](cur);
                    if (next > 200000 || next < 0) continue;
                    int dist = visited[cur] + (i == 2 ? 0 : 1);

                    if (visited[next] == 0 || (visited[next] != 0 && visited[next] > dist))
                    {
                        visited[next] = dist;
                        q.Enqueue(next);
                    }
                }
            }
            return visited[k] - 1;
        }

        static void Main(string[] args)
        {
            string[] temp = Console.ReadLine().Split(' ');
            int n = int.Parse(temp[0]);
            int k = int.Parse(temp[1]);

            Console.WriteLine(BFS(n, k));
        }
    }
}