using System;
using System.Collections.Generic;
using System.Text;
namespace 백준5430번_AC
{
    class Program
    {
        static List<int> solution(string p, int n, int[] arr)
        {
            List<int> answer = new List<int>();
            int l = 0;
            int r = arr == null ? -1 : arr.Length - 1;
            bool isReverse = false;

            for (int i = 0; i < p.Length; i++)
            {
                if (p[i] == 'R')
                {
                    isReverse = !isReverse;
                }
                else if (p[i] == 'D')
                {
                    if (r < l)
                        return null;

                    if (isReverse)
                        r--;
                    else
                        l++;
                }
            }
            for (int i = l; i <= r; i++)
                answer.Add(arr[i]);

            if (isReverse)
                answer.Reverse();

            return answer;
        }

        static void Main(string[] argc)
        {
            int t = int.Parse(Console.ReadLine());

            StringBuilder answers = new StringBuilder();

            while (t-- > 0)
            {
                string p = Console.ReadLine();
                int n = int.Parse(Console.ReadLine());
                string tempArr = Console.ReadLine().Trim('[', ']');
                int[] arr =
                    string.IsNullOrEmpty(tempArr) ? null
                    : tempArr.Split(",").Select(int.Parse).ToArray();

                List<int> answer = solution(p, n, arr);
                if (answer != null)
                {
                    answers.Append('[');
                    for (int i = 0; i < answer.Count; i++)
                    {
                        answers.Append(i > 0 ? $",{answer[i]}" : answer[i]);
                    }
                    answers.Append(']');
                    if (t > 0) answers.AppendLine();
                }
                else
                {
                    answers.AppendLine("error");
                }
            }

            Console.WriteLine(answers.ToString());
        }
    }
}