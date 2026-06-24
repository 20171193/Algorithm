// 프로그래머스(L3) : 모두 0으로 만들기
// 문제
// 1. 트리에서 임의의 연결된 두 점을 골라 한쪽은 1 증가,
//    다른 한쪽은 1감소시켜 모든 점들의 가중치를 0으로 만들어야 함.
// 2. 만약 가능하다면 최소 몇 번만에 가능한지 return
// 조건
// 1. 정점 a : (2<=a<=300,000), (-1,000,000<=a[i]<=1,000,000), 0-based
// 2. 간선 edges : edges[i] = [u,v] (u, v는 간선으로 연결되어 있음)
// 풀이
// 1. 리프노드부터 소거 -> 차수(degree)로 리프 판별
using System;
using System.Collections.Generic;

public class Solution
{
    public long solution(int[] a, int[,] edges)
    {
        int n = a.Length;
        long[] w = Array.ConvertAll(a, x => (long)x);  // 가중치 누적
        int[] degree = new int[n];  // 차수
        bool[] done = new bool[n];  // 방문체크

        List<int>[] graph = new List<int>[n];
        for (int i = 0; i < n; i++) graph[i] = new List<int>();

        for (int i = 0; i < edges.GetLength(0); i++)
        {
            int u = edges[i, 0], v = edges[i, 1];
            graph[u].Add(v);
            graph[v].Add(u);
            degree[u]++;
            degree[v]++;
        }

        Queue<int> q = new Queue<int>();
        for (int i = 0; i < n; i++)
            if (degree[i] == 1)
                q.Enqueue(i);

        long answer = 0;
        while (q.Count > 0)
        {
            int cur = q.Dequeue();
            if (done[cur]) continue;
            done[cur] = true;

            int parent = -1;
            foreach (int next in graph[cur])
                if (!done[next]) { parent = next; break; }

            // 마지막 노드 처리
            if (parent == -1)
                return w[cur] != 0 ? -1 : answer;

            answer += Math.Abs(w[cur]);
            w[parent] += w[cur];
            degree[parent]--;
            if (degree[parent] == 1) q.Enqueue(parent);
        }

        return answer;
    }
}
