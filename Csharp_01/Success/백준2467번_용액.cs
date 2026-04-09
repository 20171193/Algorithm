using System;
using System.Security.AccessControl;

namespace 백준2467번_용액
{
    class Program
    {
        static int n;
        static int[] arr;

        static int[] solution()
        {
            int[] answer = new int[2];

            int left = 0, right = n - 1, minDiff = int.MaxValue;
            while (left < right)
            {
                int sum = arr[left] + arr[right];
                int diff = Math.Abs(sum);

                if (diff < minDiff)
                {
                    minDiff = diff;
                    answer[0] = arr[left];
                    answer[1] = arr[right];
                }

                if (sum < 0)
                    left++;
                else
                    right--;
            }

            return answer;
        }

        static void Main(string[] args)
        {
            n = int.Parse(Console.ReadLine());
            arr = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();

            int[] answer = solution();
            Console.WriteLine($"{answer[0]} {answer[1]}");
        }
    }
}