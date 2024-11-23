using System;

namespace 백준11444번_피보나치_수_6
{
    class Program
    {
        // 행렬 곱
        // 메모이제이션

        public const int ModeNumber = 1000000007;
        public static Dictionary<long, int> dp = new Dictionary<long, int>();
        // n % 2 == 1
        // f(n) = f(n/2)^2 + f(n/2+1)^2

        // n % 2 == 0
        // f(n) = f(n/2+1)^2 - f(n/2-1)^2

        public static int Fibo(long n)
        {
            if (dp.ContainsKey(n))
                return dp[n];

            if ((n & 1) != 0)
            {
                long left = Fibo(n >> 1) % ModeNumber;
                long right = Fibo((n >> 1) + 1) % ModeNumber;
                int ret = (int)((left * left + right * right) % ModeNumber);
                dp[n] = ret;
                return ret;
            }
            else
            {
                long left = Fibo((n >> 1) - 1) % ModeNumber;
                long right = Fibo((n >> 1) + 1) % ModeNumber;
                int ret = (int)((right * right - left * left) % ModeNumber);

                if (ret < 0)
                    ret += ModeNumber;

                dp[n] = ret;
                return ret;
            }
        }

        static void Main(string[] args)
        {
            long n = long.Parse(Console.ReadLine());
            dp[0] = 0;
            dp[1] = 1;
            dp[2] = 1;
            Console.WriteLine(Fibo(n));
        }
    }
}