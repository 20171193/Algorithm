using System;
using System.Text;

namespace 백준1655번_가운데를_말해요
{
    class Program
    {
        static StringBuilder solve(int[] arr)
        {
            StringBuilder answer = new StringBuilder();

            PriorityQueue<int, int> maxFirstQ = new PriorityQueue<int, int>();
            PriorityQueue<int, int> minFirstQ = new PriorityQueue<int, int>();

            for (int i = 0; i < arr.Length; i++)
            {
                if (maxFirstQ.Count <= minFirstQ.Count)
                    maxFirstQ.Enqueue(arr[i], -arr[i]);
                else
                    minFirstQ.Enqueue(arr[i], arr[i]);

                while (minFirstQ.Count > 0 && maxFirstQ.Peek() > minFirstQ.Peek())
                {
                    // swap
                    int mValue = maxFirstQ.Dequeue();
                    int nValue = minFirstQ.Dequeue();

                    maxFirstQ.Enqueue(nValue, -nValue);
                    minFirstQ.Enqueue(mValue, mValue);
                }

                answer.AppendLine($"{maxFirstQ.Peek()}");
            }

            return answer;
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            int[] arr = new int[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = int.Parse(Console.ReadLine());
            }

            Console.WriteLine(solve(arr).ToString());
        }
    }
}