using System;
using System.Collections.Generic;
using System.Net.Http.Headers;
public class Solution
{
    // BFS 탐색
    static int[] BFS(int start, in List<int>[] edges)
    {
        int[] visited = new int[edges.Length];

        Queue<int> q = new Queue<int>();
        visited[start] = 1;
        q.Enqueue(start);

        while (q.Count > 0)
        {
            int cur = q.Dequeue();
            if (edges[cur] == null || edges[cur].Count == 0)
                continue;

            for (int i = 0; i < edges[cur].Count; i++)
            {
                int next = edges[cur][i];

                if (visited[next] > 0)
                {
                    visited[next] = Math.Min(visited[next], visited[cur] + 1);
                    continue;
                }

                visited[next] = visited[cur] + 1;
                q.Enqueue(next);
            }
        }

        return visited;
    }

    public int[] solution(int n, int[,] roads, int[] sources, int destination)
    {
        int[] answer = new int[sources.Length];

        // 간선 포맷
        List<int>[] edges = new List<int>[n + 1];
        for (int i = 0; i < roads.GetLength(0); i++)
        {
            int s = roads[i, 0];
            int e = roads[i, 1];

            if (edges[s] == null)
                edges[s] = new List<int>();
            edges[s].Add(e);

            if (edges[e] == null)
                edges[e] = new List<int>();
            edges[e].Add(s);
        }


        // *역으로 탐색
        // - destination 노드에서 각 노드(sources) 노드들에 이르는 최단 거리를 구하기
        // - 가중치 없음, 사이클 무시가능
        // - BFS 탐색
        int[] results = BFS(destination, edges);
        for (int i = 0; i < sources.Length; i++)
        {
            int result = results[sources[i]];
            answer[i] = result == 0 ? -1 : result - 1; // 시작지점을 1로 마킹
        }

        return answer;
    }
}