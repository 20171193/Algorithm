
namespace 백준14501번_퇴사
{
    struct Work
    {
        public int time;
        public int prop;
        public Work(int time, int prop)
        {
            this.time = time;
            this.prop = prop;
        }
    }

    class Program
    {
        static int Solve(int n, Work[] works)
        {
            int[] dp = new int[n + 2];

            for (int i = n; i >= 1; i--)
            {
                int time = works[i].time;
                int prop = works[i].prop;

                if (i + time - 1 > n)
                    dp[i] = dp[i + 1];
                else
                    dp[i] = Math.Max(dp[i + 1], prop + dp[i + time]);

            }

            return dp[1];
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            Work[] works = new Work[n + 1];
            for (int i = 1; i <= n; i++)
            {
                string[] tp = Console.ReadLine().Split(' ');
                Work work = new Work(int.Parse(tp[0]), int.Parse(tp[1]));
                works[i] = work;
            }

            Console.WriteLine(Solve(n, works));
        }
    }
}