using System;
using System.Runtime.Intrinsics;

namespace 백준25308번_방사형_그래프
{
    class Program
    {
        // 8개의 수를 나열하는 경우의 수 : 8! = 40320
        // 모든 경우의 수

        struct Vector2
        {
            public double x;
            public double y;
            public Vector2(double x, double y)
            {
                this.x = x;
                this.y = y;
            }
        }

        // 외적
        static bool CheckConvex(int[] nums)
        {
            // 라디안 45도
            double radian = Math.PI / 4;

            for (int p1 = 0; p1 < nums.Length; p1++)
            {
                int p2 = (p1 + 1) % nums.Length;
                int p3 = (p1 + 2) % nums.Length;

                // 방향 벡터
                Vector2 v1 = new Vector2(nums[p1] * Math.Cos(radian * p1), nums[p1] * Math.Sin(radian * p1));
                Vector2 v2 = new Vector2(nums[p2] * Math.Cos(radian * p2), nums[p2] * Math.Sin(radian * p2));
                Vector2 v3 = new Vector2(nums[p3] * Math.Cos(radian * p3), nums[p3] * Math.Sin(radian * p3));

                Vector2 v12 = new Vector2(v2.x - v1.x, v2.y - v1.y);
                Vector2 v13 = new Vector2(v3.x - v1.x, v3.y - v1.y);

                // 외적 v12 X v13
                double cross = v12.x * v13.y - v12.y * v13.x;
                if (cross < 0)
                    return false;
            }
            return true;
        }

        // 순열
        static void Solve(int[] nums, int[] perm, int depth, bool[] used, ref int answer)
        {
            if (depth == nums.Length)
            {
                if (CheckConvex(perm))
                    answer++;
                return;
            }

            for (int i = 0; i < nums.Length; i++)
            {
                if (used[i]) continue;

                perm[depth] = nums[i];
                used[i] = true;
                Solve(nums, perm, depth + 1, used, ref answer);
                used[i] = false;
            }
        }

        static void Main(string[] argc)
        {
            int[] nums = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
            int answer = 0;
            Solve(nums, new int[8], 0, new bool[8], ref answer);
            Console.WriteLine(answer);
        }
    }
}