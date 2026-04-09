using System.Text;

namespace 백준15666번_N과M12
{
    class Program
    {
        static void Go(int c, int depth, int[] cur, int m, int[] arr, ref StringBuilder answer)
        {
            if (depth >= m)
            {
                for (int i = 0; i < cur.Length; i++)
                {
                    answer.Append(cur[i]);
                    answer.Append(' ');
                }
                answer.Length--;
                answer.AppendLine();
                return;
            }

            // 중복된 숫자 처리
            int used = -1;

            for (int i = c; i < arr.Length; i++)
            {
                if (used != arr[i])
                {
                    cur[depth] = arr[i];
                    Go(i, depth + 1, cur, m, arr, ref answer);
                    used = arr[i];
                }
            }
        }

        static StringBuilder solution(int n, int m, int[] arr)
        {
            StringBuilder answer = new StringBuilder();
            Array.Sort(arr);
            Go(0, 0, new int[m], m, arr, ref answer);
            return answer;
        }

        static void Main(string[] args)
        {
            string[] nm = Console.ReadLine().Split(" ");
            int[] arr = Console.ReadLine().Split(" ").Select(int.Parse).ToArray();

            Console.WriteLine(solution(int.Parse(nm[0]), int.Parse(nm[1]), arr).ToString());
        }
    }
}