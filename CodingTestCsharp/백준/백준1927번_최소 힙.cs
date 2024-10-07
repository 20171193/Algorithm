using System;
using System.Text;
using System.Threading.Channels;

namespace 백준1927번_최소_힙
{
    class Program
    {
        // 0< : 값 추가
        // 0==: 가장 작은 값 출력후 제거
        static StringBuilder solution(int n, string[] orders)
        {
            StringBuilder answer = new StringBuilder();
            PriorityQueue<string, int> pq = new PriorityQueue<string, int>();

            for (int i = 0; i < orders.Length; i++)
            {
                if (orders[i] == "0")
                    answer.AppendLine(pq.Count > 0 ? pq.Dequeue() : "0");
                else
                    pq.Enqueue(orders[i], int.Parse(orders[i]));
            }
            return answer;
        }
        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            string[] orders = new string[n];

            for (int i = 0; i < n; i++)
                orders[i] = Console.ReadLine();

            // 출력시간 줄여야함.
            // Console.WriteLine이 호출될 때마다 출력 버퍼에 접근.
            Console.WriteLine(solution(n, orders).ToString());
        }
    }
}