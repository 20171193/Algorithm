using System;

namespace 백준18111번_마인크래프트
{
    class Program
    {
        // 1. 블록 제거하고 인벤토리에 삽입 (2초)
        // 2. 블록 꺼내서 설치 (1초)
        // 설치 or 제거

        static int[] Solution(Dictionary<int, int> heights, in int[,] arr, int n, int m, int b, int maxHeight, int minHeight)
        {
            int[] answer = new int[2] { int.MaxValue, -1 };
            int size = n * m;

            int l = minHeight;
            int r = maxHeight;
            if (l == r)
                return new int[2] { 0, maxHeight };

            for (int targetHeight = maxHeight; targetHeight >= minHeight; targetHeight--)
            {
                // 소요시간 
                int time = 0;
                // 필요 블록 개수
                int needs = 0;

                // 시간, 블록처리
                foreach (int height in heights.Keys)
                {
                    if (targetHeight == height)
                        continue;

                    // 목표 높이와 현재 높이의 차
                    int differ = targetHeight - height;
                    // 설치 혹은 수거할 블록의 개수
                    int curBlocks = Math.Abs(differ * heights[height]);

                    // 설치해야하는 경우
                    if (differ > 0)
                    {
                        needs += curBlocks;
                        time += curBlocks;
                    }
                    // 수거해야하는 경우
                    else
                    {
                        needs -= curBlocks;
                        time += curBlocks * 2;
                    }
                }

                // 필요한 블럭이 소지한 블록보다 많은 경우
                if (needs > b)
                    continue;

                // 답 갱신
                if (answer[0] > time)
                {
                    answer[0] = time;
                    answer[1] = targetHeight;
                }
                else
                    break;
            }

            return answer;
        }

        static void Main(string[] args)
        {
            Dictionary<int, int> heights = new Dictionary<int, int>();

            string[] temp = Console.ReadLine().Split(' ');
            int n = int.Parse(temp[0]);
            int m = int.Parse(temp[1]);
            int b = int.Parse(temp[2]);

            int[,] arr = new int[n, m];
            int minHeight = int.MaxValue, maxHeight = -1;
            for (int i = 0; i < n; i++)
            {
                temp = Console.ReadLine().Split(' ');
                for (int j = 0; j < temp.Length; j++)
                {
                    int value = int.Parse(temp[j]);
                    arr[i, j] = value;
                    if (heights.ContainsKey(value))
                        heights[value]++;
                    else
                        heights[value] = 1;

                    minHeight = Math.Min(minHeight, value);
                    maxHeight = Math.Max(maxHeight, value);
                }
            }

            int[] answer = Solution(heights, in arr, n, m, b, maxHeight, minHeight);
            Console.WriteLine($"{answer[0]} {answer[1]}");
        }
    }
}