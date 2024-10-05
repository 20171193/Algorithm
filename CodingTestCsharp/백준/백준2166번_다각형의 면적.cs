using System;

namespace 백준2166번_다각형의_면적
{
    class Program
    {
        public struct Pos
        {
            public int x = 0;
            public int y = 0;
            public Pos(int x, int y)
            {
                this.x = x;
                this.y = y;
            }
        }
        static double solution(int n, Pos[] positions)
        {
            long answer = 0;

            // 신발끈 공식 사용
            for (int fst = 0; fst < n; fst++)
            {
                int sec = (fst + 1) % n;
                answer += (long)positions[fst].x * positions[sec].y;
                answer -= (long)positions[fst].y * positions[sec].x;
            }
            return Math.Abs(answer) / 2.0;
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            Pos[] positions = new Pos[n];
            for (int i = 0; i < n; i++)
            {
                string[] temp = Console.ReadLine().Split(' ');
                positions[i] = new Pos(int.Parse(temp[0]), int.Parse(temp[1]));
            }
            double area = solution(n, positions);
            // 소수점 첫째자리까지 '꼭' 출력;;
            Console.WriteLine(area.ToString("F1"));
        }
    }
}