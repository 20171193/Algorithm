using System;
using System.Text;

namespace 백준9019번_DSLR
{
    class Program
    {
        // 0 <= n < 10,000
        // n의 네자리수 d1,d2,d3,d4
        // D : n = 2*n % 10000
        // S : n = n-1, if(n-1 < 0) n = 9999
        // L : 자리수를 왼쪽으로 회전 -> d2, d3, d4, d1
        // R : 자리수를 오른쪽으로 회전 -> d4, d1, d2, d3

        // 변환옵션 (DSLR)
        static Func<int, int>[] DSLR = new Func<int, int>[]
        {
            // n*2%10000
            (value) => value = value*2 % 10000,
            // n-1
            (value) =>
            {
                if(value == 0)
                    return 9999;
                else
                    return value-1;
            },
            // 왼쪽 회전
            (value) =>
            {
                if(value == 0)
                    return 0;
                // 제일 큰 자리수 할당
                int front = value/1000;
                return value * 10 % 10000 + front;
            },
            // 오른쪽 회전
            (value) =>
            {
                if(value == 0)
                    return 0;
                int back = value%10;
                return ((value / 10) + (back*1000)) % 10000;
            }
        };

        static string solution(string A, string B)
        {
            string answer = "";
            string option = "DSLR";
            // BFS
            StringBuilder[] path = new StringBuilder[10001];
            Queue<int> q = new Queue<int>();
            int curNum = int.Parse(A);
            q.Enqueue(curNum);
            path[curNum] = new StringBuilder();

            while (q.Count > 0)
            {
                curNum = q.Dequeue();

                // 이미 목적지 경로가 나왔고 현재 경로가 목적지 경로보다 긴 경우 continue
                if (answer.Length != 0 && answer.Length <= path[curNum].Length)
                    continue;

                for (int i = 0; i < 4; i++)
                {
                    int nextNum = DSLR[i](curNum);

                    // 이미 확인한 숫자라면
                    if (path[nextNum] != null)
                    {
                        // 더 짧은 경로로 갱신
                        if (path[nextNum].Length > path[curNum].Length + 1)
                        {
                            path[curNum].Append(option[i]);
                            path[nextNum] = new StringBuilder(path[curNum].ToString());
                        }
                    }
                    else
                    {
                        path[nextNum] = new StringBuilder(path[curNum].ToString());
                        path[nextNum].Append(option[i]);
                        q.Enqueue(nextNum);
                    }

                    // answer 갱신
                    if (nextNum == int.Parse(B))
                    {
                        if (answer.Length == 0 || answer.Length > path[nextNum].Length)
                            answer = path[nextNum].ToString();
                    }
                }
            }

            return answer;
        }

        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine());
            while (t-- > 0)
            {
                string[] AB = Console.ReadLine().Split(" ");
                Console.WriteLine(solution(AB[0], AB[1]));
            }
        }
    }
}