using System;

namespace 백준1753번_최단경로
{
    class Program
    {
        struct Edge
        {
            public int e;
            public int v;
            public Edge(int e, int v)
            {
                this.e = e;
                this.v = v;
            }
        }

        static List<int> Dijkstra(int start, int v, in List<List<Edge>> edges)
        {
            List<int> dists = new List<int>();
            for (int i = 0; i <= v; i++)
                dists.Add(i == start ? 0 : int.MaxValue);

            PriorityQueue<Edge, int> pq = new PriorityQueue<Edge, int>();
            pq.Enqueue(new Edge(start, 0), 0);

            while (pq.Count > 0)
            {
                Edge cur = pq.Dequeue();
                if (dists[cur.e] < cur.v)
                    continue;

                for (int i = 0; i < edges[cur.e].Count; i++)
                {
                    int nextNode = edges[cur.e][i].e;
                    int dist = edges[cur.e][i].v;

                    if (dists[nextNode] <= dist + cur.v)
                        continue;

                    dists[nextNode] = dist + cur.v;
                    pq.Enqueue(new Edge(nextNode, dists[nextNode]), dists[nextNode]);
                }
            }

            return dists;
        }

        static void Main(string[] argc)
        {
            string[] temp = Console.ReadLine().Split(' ');
            int v = int.Parse(temp[0]);
            int e = int.Parse(temp[1]);
            int k = int.Parse(Console.ReadLine());

            // 간선 배열 초기화
            List<List<Edge>> edges = new List<List<Edge>>();
            for (int i = 0; i <= v; i++)
                edges.Add(new List<Edge>());

            for (int i = 0; i < e; i++)
            {
                temp = Console.ReadLine().Split(' ');
                int start = int.Parse(temp[0]);
                int end = int.Parse(temp[1]);
                int value = int.Parse(temp[2]);

                edges[start].Add(new Edge(end, value));
            }

            List<int> answer = Dijkstra(k, v, in edges);
            for (int i = 1; i < answer.Count; i++)
                Console.WriteLine(answer[i] == int.MaxValue ? "INF" : answer[i]);

        }
    }
}