using System;
using System.ComponentModel.Design;
using System.Numerics;
using System.Runtime.CompilerServices;

namespace 백준1074_Z
{
    class Program
    {
        static int N = 0, r = 0, c = 0;

        // 영역 내부에 (r,c)가 존재하는지 확인
        static bool CheckBound(int range, int y, int x)
        {
            return (c >= x && c < x + range) && (r >= y && r < y + range);
        }

        static int solution(int edge, int y, int x)
        {
            // 기저조건
            if (edge == 1)
                return 0;

            int ret = 0;
            int half = edge / 2;
            // r c의 위치 확인
            // 2사분면에 존재
            if (CheckBound(half, y, x))
                ret += solution(half, y, x);
            // 1사분면에 존재
            else if (CheckBound(half, y, x + half))
                ret += half * half + solution(half, y, x + half);
            // 3사분면에 존재
            else if (CheckBound(half, y + half, x))
                ret += half * half * 2 + solution(half, y + half, x);
            // 4사분면에 존재
            else
                ret += half * half * 3 + solution(half, y + half, x + half);

            return ret;
        }

        static void Main()
        {
            string[] temp = Console.ReadLine().Split(' ');
            N = int.Parse(temp[0]);
            r = int.Parse(temp[1]);
            c = int.Parse(temp[2]);
            Console.WriteLine(solution((int)Math.Pow(2, N), 0, 0));
        }
    }
}