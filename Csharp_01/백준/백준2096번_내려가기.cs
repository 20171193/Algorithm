namespace 백준2096번_내려가기
{
    class Program
    {
        static int IMax(params int[] nums)
        {
            int ret = int.MinValue;
            for (int i = 0; i < nums.Length; i++)
            {
                ret = Math.Max(nums[i], ret);
            }
            return ret;
        }
        static int IMin(params int[] nums)
        {
            int ret = int.MaxValue;
            for (int i = 0; i < nums.Length; i++)
            {
                ret = Math.Min(nums[i], ret);
            }
            return ret;
        }

        static int[] solution(int n, int[,] arr)
        {
            int[] answer = new int[2];
            int[,] mxDP = new int[n, 3];
            int[,] mnDP = new int[n, 3];
            // 초기화
            for (int i = 0; i < 3; i++)
                mxDP[0, i] = mnDP[0, i] = arr[0, i];

            for (int i = 1; i < n; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    mxDP[i, j] =
                        IMax(mxDP[i - 1, j],
                        j > 0 ? mxDP[i - 1, j - 1] : -1,
                        j < 2 ? mxDP[i - 1, j + 1] : -1) + arr[i, j];
                    mnDP[i, j] =
                        IMin(mnDP[i - 1, j],
                        j > 0 ? mnDP[i - 1, j - 1] : int.MaxValue,
                        j < 2 ? mnDP[i - 1, j + 1] : int.MaxValue) + arr[i, j];
                }
            }
            answer[0] = IMax(mxDP[n - 1, 0], mxDP[n - 1, 1], mxDP[n - 1, 2]);
            answer[1] = IMin(mnDP[n - 1, 0], mnDP[n - 1, 1], mnDP[n - 1, 2]);

            return answer;
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            int[,] arr = new int[n, 3];
            for (int i = 0; i < n; i++)
            {
                int[] temp = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();

                for (int j = 0; j < 3; j++)
                    arr[i, j] = temp[j];
            }

            int[] answer = solution(n, arr);
            Console.WriteLine($"{answer[0]} {answer[1]}");
        }
    }
}