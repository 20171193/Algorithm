using System;
using System.Net.WebSockets;
using System.Text;

namespace 백준15655번_N과M_6
{
    class Program
    {
        static void Comb(int c, int depth, int[] choose, int m, in int[] arr, ref StringBuilder answer)
        {
            if (depth == m)
            {
                answer.AppendLine(string.Join(" ", choose));
                return;
            }

            for (int i = c; i < arr.Length; i++)
            {
                if (arr.Length - i < m - depth)
                    return;

                choose[depth] = arr[i];
                Comb(i + 1, depth + 1, choose, m, in arr, ref answer);
                choose[depth] = 0;
            }
        }

        static StringBuilder solution(int n, int m, int[] arr)
        {
            StringBuilder answer = new StringBuilder();
            Array.Sort(arr);
            Comb(0, 0, new int[m], m, in arr, ref answer);
            return answer;
        }

        static void Main()
        {
            string[] nm = Console.ReadLine().Split(' ');
            int[] arr = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
            Console.WriteLine(solution(int.Parse(nm[0]), int.Parse(nm[1]), arr).ToString());
        }
    }
}