using System;
using System.Runtime.CompilerServices;
using System.Text;

namespace 백준1676번_팩토리얼_0의_개수
{
    // 3 2 1
    // 6 6
    // 90 720 4 4 0
    class Program
    {
        static void Main(string[] args)
        {
            HashSet<long> set = new HashSet<long>();

            int n = int.Parse(Console.ReadLine());
            string[] temp = Console.ReadLine().Split(' ');
            for (int i = 0; i < n; i++)
                set.Add(int.Parse(temp[i]));

            int m = int.Parse(Console.ReadLine());
            temp = Console.ReadLine().Split(' ');
            StringBuilder answer = new StringBuilder();
            for (int i = 0; i < m; i++)
            {
                if (set.Contains(int.Parse(temp[i])))
                    answer.AppendLine("1");
                else
                    answer.AppendLine("0");
            }

            Console.WriteLine(answer.ToString());
        }
    }
}