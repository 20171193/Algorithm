using System;
using System.Text;

namespace 백준2252번_줄_세우기
{
    class Program
    {
        static string solve(int n, List<int>[] edges)
        {
            StringBuilder answer = new StringBuilder();

            int[] inDegree = new int[n + 1];
            for (int i = 1; i < edges.Length; i++)
                for (int j = 0; j < edges[i].Count; j++)
                    inDegree[edges[i][j]]++;

            Queue<int> q = new Queue<int>();
            for (int i = 1; i <= n; i++)
            {
                if (inDegree[i] == 0)
                    q.Enqueue(i);
            }

            while (q.Count > 0)
            {
                int cur = q.Dequeue();
                answer.Append($"{cur} ");
                for (int i = 0; i < edges[cur].Count; i++)
                {
                    int next = edges[cur][i];

                    inDegree[next]--;
                    if (inDegree[next] == 0)
                        q.Enqueue(next);
                }
            }
            answer.Length--;

            return answer.ToString();
        }

        static void Main(string[] args)
        {
            string[] nm = Console.ReadLine().Split(' ');
            int n = int.Parse(nm[0]);
            int m = int.Parse(nm[1]);

            List<int>[] edges = new List<int>[n + 1];
            for (int i = 1; i <= n; i++)
                edges[i] = new List<int>();

            for (int i = 0; i < m; i++)
            {
                string[] ab = Console.ReadLine().Split(' ');
                int a = int.Parse(ab[0]);
                int b = int.Parse(ab[1]);

                edges[a].Add(b);
            }

            Console.WriteLine(solve(n, edges));
        }
    }
}