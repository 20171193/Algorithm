using System.Runtime.InteropServices;

namespace 백준9663번_NQueen
{
    class Program
    {
        static bool Check(int y, in int[] arr)
        {
            for (int x = 0; x < y; x++)
            {
                // 상하
                if (arr[y] == arr[x])
                    return false;
                // 대각
                if (y - x == Math.Abs(arr[y] - arr[x]))
                    return false;
            }
            return true;
        }

        static int Go(int y, int[] arr)
        {
            if (y == arr.Length)
            {
                return 1;
            }

            int count = 0;

            for (int i = 0; i < arr.Length; i++)
            {
                arr[y] = i;
                if (Check(y, in arr))
                    count += Go(y + 1, arr);
            }
            return count;
        }

        static int solution(int n)
        {
            return Go(0, new int[n]);
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            Console.WriteLine(solution(n));
        }
    }
}