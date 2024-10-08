namespace 백준1916번_최소비용_구하기
{
    class Program
    {
        // n개의 도시, m개의 버스
        // a에서 b까지 가는 최소비용

        public struct InputEdge
        {
            public int start;
            public int end;
            public int cost;

            public InputEdge(params int[] v)
            {
                this.start = v[0];
                this.end = v[1];
                this.cost = v[2];
            }
        }
        public struct Edge
        {
            public int start;
            public int end;
            public Edge(params int[] v)
            {
                this.start = v[0];
                this.end = v[1];
            }
        }

        static int bfs(int n, int s, int e, Dictionary<Edge, int> dic)
        {
            int ret = int.MaxValue;

            Queue<int> q = new Queue<int>();
            int[] visited = new int[n + 1];
            visited[s] = 1;

            q.Enqueue(s);
            while (q.Count > 0)
            {
                int cur = q.Dequeue();
                for (int i = 1; i <= n; i++)
                {
                    Edge edge = new Edge(cur, i);
                    if (cur == i)
                        continue;
                    if (!dic.ContainsKey(edge))
                        continue;
                    if (visited[i] > 0)
                    {
                        visited[i] = Math.Min(visited[i], visited[cur] + dic[edge]);
                        continue;
                    }

                    visited[i] = visited[cur] + dic[edge];
                    q.Enqueue(i);
                }
            }
            ret = visited[e] - 1;
            return ret;
        }

        static int solution(int n, int m, int s, int e, InputEdge[] edges)
        {
            int answer = -1;
            Dictionary<Edge, int> dic = new Dictionary<Edge, int>();

            for (int i = 0; i < edges.Length; i++)
            {
                dic.Add(new Edge(edges[i].start, edges[i].end), edges[i].cost);
            }
            answer = bfs(n, s, e, dic);
            return answer;
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            int m = int.Parse(Console.ReadLine());

            InputEdge[] edges = new InputEdge[m];
            for (int i = 0; i < m; i++)
            {
                edges[i] = new InputEdge(Console.ReadLine().Split(' ').Select(int.Parse).ToArray());
            }

            int[] se = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();

            Console.WriteLine(solution(n, m, se[0], se[1], edges));
        }
    }
}