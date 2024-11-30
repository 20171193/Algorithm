using System;
using System.Net.Http.Headers;
using System.Text;

namespace 백준11403번_경로_찾기
{
    class Program
    {
        // 비트마스킹 + BFS ( n < 31 )
        static StringBuilder solution(int n, List<int> bits)
        {
            StringBuilder ret = new StringBuilder();
            int visited = 0;
            Queue<int> q = new Queue<int>();

            for (int i = 0; i < n; i++)
            {
                q.Enqueue(i);

                while (q.Count > 0)
                {
                    int cur = q.Dequeue();
                    for (int b = 0; b < n; b++)
                    {
                        int next = (1 << b);
                        if ((bits[cur] & next) == 0)
                            continue;
                        if ((visited & next) > 0)
                            continue;

                        visited |= 1 << b;
                        q.Enqueue(b);
                    }
                }

                for (int j = 0; j < n; j++)
                {
                    if ((visited & (1 << j)) > 0)
                        ret.Append("1 ");
                    else
                        ret.Append("0 ");
                }
                ret.Length--;
                ret.AppendLine();
                visited = 0;
            }

            ret.Length--;
            return ret;
        }

        // BFS
        static StringBuilder solution(int n, List<int>[] edges)
        {
            StringBuilder ret = new StringBuilder();
            bool[] visited = new bool[n];
            Queue<int> q = new Queue<int>();

            for (int i = 0; i < n; i++)
            {
                q.Enqueue(i);

                while (q.Count > 0)
                {
                    int cur = q.Dequeue();
                    for (int j = 0; j < edges[cur].Count; j++)
                    {
                        int next = edges[cur][j];

                        if (visited[next])
                            continue;

                        visited[next] = true;
                        q.Enqueue(next);
                    }
                }

                for (int j = 0; j < n; j++)
                    ret.Append(visited[j] ? "1 " : "0 ");
                ret.Length--;
                ret.AppendLine();
                Array.Fill(visited, false);
            }
            ret.Length--;
            return ret;
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());

            // 비트마스킹
            if (n < 31)
            {
                List<int> bits = new List<int>(n);
                for (int i = 0; i < n; i++)
                {
                    string str = Console.ReadLine();
                    bits.Add(0);
                    int bIndex = -1;
                    for (int j = 0; j < str.Length; j += 2)
                    {
                        bIndex++;
                        if (str[j] == '0')
                            continue;
                        bits[i] |= (1 << bIndex);
                    }
                }
                Console.WriteLine(solution(n, bits));
            }
            // 그래프
            else
            {
                List<int>[] edges = new List<int>[n];
                for (int i = 0; i < n; i++)
                {
                    string str = Console.ReadLine();
                    edges[i] = new List<int>();
                    int index = -1;
                    for (int node = 0; node < str.Length; node += 2)
                    {
                        index++;
                        if (str[node] == '0')
                            continue;

                        edges[i].Add(index);
                    }
                }

                Console.WriteLine(solution(n, edges).ToString());

            }
        }
    }
}