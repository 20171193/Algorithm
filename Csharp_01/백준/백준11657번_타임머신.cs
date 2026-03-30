using System;
using System.ComponentModel.Design;
using System.Data;
using System.Text;

namespace 백준11657번_타임머신
{
    // 시도 1. foreach로 Dictionary순회 2번 반복 (시간초과)
    // 시도 2. Dictionary를 List로 파싱 후 진행 (출력초과) 
    // 시도 3. 거리배열을 int -> long으로 수정
    //         - 최대 노드 500개고 최대 거리 10000이라서 int이상 안갈줄암.
    //         - 거리 갱신중에 양의 사이클을 고려못함 (밸만포드는 음의 사이클만 판단)

    // 벨만포드
    // - 가중치 그래프에서 한 노드에서 모든 노드에 이르는 최단 거리를 찾는 알고리즘
    // - 음수 가중치를 처리할 수 있음. 음수 사이클 탐지가 가능
    // vs 다익스트라
    // - 다익스트라는 음수 가중치에 대한 처리가 불가
    // - 방문한 노드에 가중치를 업데이트하는 BFS도 마찬가지
    class Program
    {
        struct Edge
        {
            public int start = 0;
            public int end = 0;

            public Edge(int start, int end)
            {
                this.start = start;
                this.end = end;
            }
        };

        static bool solution(int n, int m, Dictionary<Edge, int> edges, out long[] answer)
        {
            long[] dists = new long[n + 1];
            Array.Fill(dists, long.MaxValue);    // 모든 거리를 최대 가중치로 초기화
            dists[1] = 0;  // 시작 노드는 1
            var edgeList = edges.ToList();
            // 정점개수 - 1 만큼 간선을 확인 
            for (int i = 0; i < n - 1; i++)
            {
                // 간선개수만큼 진행
                for (int j = 0; j < edgeList.Count; j++)
                {
                    Edge edge = edgeList[j].Key;
                    int value = edgeList[j].Value;

                    // 현재노드에 대한 가중치가 없을 경우
                    if (dists[edge.start] == long.MaxValue)
                        continue;
                    // 가중치 갱신
                    dists[edge.end] = Math.Min(dists[edge.end], dists[edge.start] + value);
                }
            }


            // 간선개수만큼 진행
            for (int j = 0; j < edgeList.Count; j++)
            {
                Edge edge = edgeList[j].Key;
                int value = edgeList[j].Value;

                // 현재노드, 다음 노드에 대한 가중치가 존재하지 않는 경우
                if (dists[edge.start] == long.MaxValue || dists[edge.start] == long.MaxValue)
                    continue;
                // 재탐색 과정에서 비용이 줄어든다면 음수 사이클
                if (dists[edge.end] > dists[edge.start] + value)
                {
                    answer = new long[1] { -1 };
                    return false;
                }
            }
            // 결과값 할당
            answer = new long[n - 1];  // 1을 제외한 나머지 노드까지의 거리
            for (int i = 2; i <= n; i++)
            {
                if (dists[i] == long.MaxValue)
                    answer[i - 2] = -1;
                else
                    answer[i - 2] = dists[i];
            }
            return true;
        }


        static void Main(string[] argc)
        {
            string[] inputs = Console.ReadLine().Split(" ");
            int n = int.Parse(inputs[0]);
            int m = int.Parse(inputs[1]);

            Dictionary<Edge, int> edges = new Dictionary<Edge, int>();

            for (int i = 0; i < m; i++)
            {
                int s = 0, e = 0, v = 0;
                inputs = Console.ReadLine().Split(" ");
                s = int.Parse(inputs[0]);
                e = int.Parse(inputs[1]);
                v = int.Parse(inputs[2]);

                Edge edge = new Edge(s, e);
                if (edges.ContainsKey(edge))
                    edges[edge] = Math.Min(v, edges[edge]);
                else
                    edges.Add(edge, v);
            }


            if (solution(n, m, edges, out long[] answer))
            {
                StringBuilder output = new StringBuilder();
                for (int i = 0; i < answer.Length; i++)
                    output.AppendLine($"{answer[i]}");
                output.Length--;
                Console.WriteLine(output.ToString());
            }
            else
                Console.WriteLine(-1);
        }
    }
}
