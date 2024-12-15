using System;
using System.Text;

namespace 백준2312번_수_복원하기
{
    class Program
    {
        const int maxSize = 100000;
        static bool[] isPrime = new bool[maxSize + 1];
        static void Eratosthenes()
        {
            for (int i = 2; i <= maxSize; i++)
                isPrime[i] = true;

            for (int i = 2; i <= maxSize; i++)
            {
                if (isPrime[i])
                {
                    for (long j = (long)i * i; j <= maxSize; j += i)
                        isPrime[j] = false;
                }
            }
        }

        static string solve(int num)
        {
            StringBuilder ret = new StringBuilder();

            int tempNum = num;
            for (int i = 2; i <= num; i++)
            {
                if (isPrime[i] == false)
                    continue;

                int count = 0;
                while (tempNum % i == 0)
                {
                    tempNum /= i;
                    count++;
                }

                if (count > 0)
                    ret.AppendLine($"{i} {count}");
            }
            return ret.ToString();
        }

        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine());
            StringBuilder answer = new StringBuilder();
            Eratosthenes();
            while (t-- > 0)
            {
                answer.Append(solve(int.Parse(Console.ReadLine())));
            }
            answer.Length--;
            Console.WriteLine(answer.ToString());
        }
    }
}