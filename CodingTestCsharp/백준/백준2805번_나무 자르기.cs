namespace 백준2805번_나무_자르기
{
    class Program
    {
        // 시간초과 코드(인덱스 탐색 -> 길이 탐색)

        // 적어도 M미터의 나무 - 절단기의 높이를 최대로 최소 M이상 잘라야함.
        static int solution1(int n, int m, int[] arr)
        {
            int answer = 0;
            Array.Sort(arr, (a, b) => b.CompareTo(a));
            // 가장 높은 나무에서부터 m만큼 잘릴때까지 탐색 (인덱스 탐색)
            int cutIndex = -1;
            for (int i = 1; i < arr.Length; i++)
            {
                int temp = 0;
                for (int j = i - 1; j >= 0; j--)
                {
                    temp += arr[j] - arr[i];
                }

                if (temp >= m)
                {
                    cutIndex = i;
                    break;
                }
            }

            // arr[cutIndex]부터 arr[0]까지 길이가 최대가 될때까지 자르기
            for (int length = arr[cutIndex]; length < arr[0]; length++)
            {
                long temp = 0;
                for (int j = cutIndex; j >= 0; j--)
                {
                    if (cutIndex >= arr.Length)
                        break;
                    // 후보군 제외 (자르려는 길이에 못미치는 나무들)
                    if (arr[j] <= length)
                    {
                        cutIndex--;
                        continue;
                    }
                    temp += arr[j] - length;
                }

                // m에 못 미칠 경우 이전 -1의 길이 할당
                if (temp < m)
                {
                    answer = length - 1;
                    break;
                }
            }
            return answer;
        }

        static long Cut(int length, int[] arr)
        {
            long ret = 0;
            for (int i = 0; i < arr.Length; i++)
            {
                if (arr[i] <= length) continue;
                ret += arr[i] - length;
            }
            return ret;
        }

        // 이분탐색
        static int solution2(int n, int m, int[] arr)
        {
            Array.Sort(arr);
            // arr[cutIndex] ~ arr[n-1] 이분탐색
            int left = 0;
            int right = arr[n - 1];

            while (left <= right)
            {
                int mid = (int)(((long)(left) + right) / 2);
                // 중간 값으로 나무 자르기 
                long cut = Cut(mid, arr);
                if (cut >= m)
                    left = mid + 1;
                else
                    right = mid - 1;
            }

            return right;
        }


        static void Main(string[] argc)
        {
            string[] temp = Console.ReadLine().Split(" ");
            int n = int.Parse(temp[0]);
            int m = int.Parse(temp[1]);
            int[] arr = Console.ReadLine().Split(" ").Select(int.Parse).ToArray();

            Console.WriteLine(solution2(n, m, arr));
        }
    }
}