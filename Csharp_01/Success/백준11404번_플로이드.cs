using System;
using System.Data;
using System.Text;
namespace 백준11404번_플로이드
{
    class Program
    {
        /// <summary>
        /// 플로이드-워셜 알고리즘 O(n^3) 
        /// </summary>
        /// <param name="matrix">변환할 행렬 그래프</param>
        static void FloydWarshall(int n, int m, ref int[,] matrix)
        {
            // 모든 노드에서 경유하는 노드를 설정하여 최저 비용 확인

            // 중간노드
            for (int mid = 1; mid <= n; mid++)
            {
                // 출발 노드
                for (int start = 1; start <= n; start++)
                {
                    if (mid == start) continue;
                    // 끝 노드
                    for (int end = 1; end <= n; end++)
                    {
                        if (start == end || mid == end) continue;

                        matrix[start, end]
                            = matrix[start, mid] == int.MaxValue || matrix[mid, end] == int.MaxValue
                            ? matrix[start, end] : Math.Min(matrix[start, end], matrix[start, mid] + matrix[mid, end]);
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            // input
            int n = int.Parse(Console.ReadLine());
            int m = int.Parse(Console.ReadLine());

            // 행렬 INF로 초기화
            int[,] matrix = new int[n + 1, n + 1];
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    matrix[i, j] = int.MaxValue;

            for (int i = 0; i < m; i++)
            {
                int a = 0, b = 0, c = 0;

                string[] temp = Console.ReadLine().Split(' ');
                a = int.Parse(temp[0]);
                b = int.Parse(temp[1]);
                c = int.Parse(temp[2]);

                matrix[a, b] = Math.Min(matrix[a, b], c);
            }

            // solve
            FloydWarshall(n, m, ref matrix);

            // output 
            StringBuilder answer = new StringBuilder();
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    answer.Append(matrix[i, j] == int.MaxValue ? 0 : matrix[i, j]);
                    if (j != n)
                        answer.Append(" ");
                }
                answer.AppendLine();
            }
            answer.Length--;
            Console.WriteLine(answer.ToString());
        }
    }
}