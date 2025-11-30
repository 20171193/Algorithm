using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodingTestCsharp.백준
{
    // 백준 1516번 : 게임 개발(https://www.acmicpc.net/problem/1516)
    // 1. 특정 건물을 지을 때 먼저 지어야하는 건물이 있음.
    //   => 진입 차수
    // 2. 여러 개 건물을 동시에 지을 수 있음. 
    class 백준1516번_게임_개발
    {
        static int[] solution(int n, int[] buildTimes, int[] inDegrees, List<List<int>> conditions)
        {
            int[] totalBuildTimes = new int[n + 1];

            Queue<int> q = new Queue<int>();

            // 차수가 0인 노드 삽입
            for (int i = 1; i <= n; i++)
            {
                if (inDegrees[i] == 0)
                {
                    q.Enqueue(i);
                    totalBuildTimes[i] = buildTimes[i];
                }
            }

            while (q.Count > 0)
            {
                int cur = q.Dequeue();

                for (int i = 0; i < conditions[cur].Count; i++)
                {
                    int next = conditions[cur][i];
                    // 동시에 건설 가능 (최대 시간만 갱신)
                    totalBuildTimes[next] = Math.Max(totalBuildTimes[next], totalBuildTimes[cur] + buildTimes[next]);
                    if (--inDegrees[next] == 0)
                        q.Enqueue(next);
                }
            }

            return totalBuildTimes;
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            // 1-based initialize
            int[] buildTimes = new int[n + 1];
            int[] inDegrees = new int[n + 1];
            List<List<int>> conditions = new List<List<int>>(n + 1);
            for (int i = 0; i <= n; i++)
                conditions.Add(new List<int>());

            for (int i = 1; i <= n; i++)
            {
                string[] temp = Console.ReadLine().Split(' ');
                buildTimes[i] = int.Parse(temp[0]);
                if (temp.Length > 2)
                {
                    for (int j = 1; j < temp.Length - 1; j++)
                    {
                        int pre = int.Parse(temp[j]);
                        conditions[pre].Add(i);
                        inDegrees[i]++;
                    }
                }
            }

            int[] answer = solution(n, buildTimes, inDegrees, conditions);
            string answerStr = string.Join(Environment.NewLine, answer.Skip(1));
            Console.WriteLine(answerStr);
        }
    }
}
