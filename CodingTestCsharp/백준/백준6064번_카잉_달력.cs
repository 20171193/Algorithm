using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace 백준6064번_카잉_달력
{
    class Program
    {
        // x,y <= M, N
        // <x:y>
        // x'는 다음해. 
        // x < M 일 경우 x' = x + 1
        // x >= M 일 경우 x' = x

        // 최소 공배수찾기 (M N으로 표현할 수 있는 마지막 주기)
        static int GetLCM(int a, int b)
        {
            // 최대 공약수 구하기
            int ta = a;
            int tb = b;
            while (tb > 0)
            {
                int temp = ta % tb;
                ta = tb;
                tb = temp;
            }

            // 최소 공배수 구하기
            return a * b / ta;
        }

        static int solution(int m, int n, int x, int y)
        {
            // 최소 공배수 = 마지막 해
            int lcm = GetLCM(m, n);
            // x기준 반복되는 주기
            while (x <= lcm)
            {
                if (x % n == y % n)
                    return x;
                x += m;
            }
            return -1;
        }

        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine());
            StringBuilder answers = new StringBuilder();
            while (t-- > 0)
            {
                int[] mnxy = Console.ReadLine().Split(" ").Select(int.Parse).ToArray();
                // $"{}" 보다 ToString이 좋다고함
                answers.AppendLine(solution(mnxy[0], mnxy[1], mnxy[2], mnxy[3]).ToString());
            }
            Console.WriteLine(answers.ToString());
        }
    }
}