using System;

namespace 백준14500번_테트로미노
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
        public struct Tetromino
        {
            public List<Pos> meshs;
            public Tetromino(Pos p1, Pos p2, Pos p3, Pos p4)
            {
                meshs = new List<Pos>() { p1, p2, p3, p4 };
            }
            public void Move(int x, int y)
            {
                for (int i = 0; i < meshs.Count; i++)
                    meshs[i] = new Pos(meshs[i].x + x, meshs[i].y + y);
            }
        }
        static bool CheckBound(ref Tetromino target, int[,] arr, out int value)
        {
            value = 0;

            for (int i = 0; i < target.meshs.Count; i++)
            {
                Pos bound = target.meshs[i];

                if (bound.y < 0 || bound.y >= arr.GetLength(0) || bound.x < 0 || bound.x >= arr.GetLength(1))
                    return false;

                value += arr[bound.y, bound.x];
            }
            return true;
        }
        static Tetromino[] MakeTetromino()
        {
            Tetromino[] tetrominos = new Tetromino[19]
            {
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(2,0), new Pos(3,0)),  // 일자 가로
                new Tetromino(new Pos(0,0), new Pos(0,1), new Pos(0,2), new Pos(0,3)),  // 일자 세로
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(0,1), new Pos(1,1)),  // 직사각형
                new Tetromino(new Pos(0,0), new Pos(0,1), new Pos(0,2), new Pos(1,2)),  // L 
                new Tetromino(new Pos(0,0), new Pos(0,1), new Pos(1,0), new Pos(2,0)),  // L 90
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(1,1), new Pos(1,2)),  // L 180
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(2,0), new Pos(2,-1)), // L 270
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(1,-1), new Pos(1,-2)),  // L 대칭 
                new Tetromino(new Pos(0,0), new Pos(0,1), new Pos(1,1), new Pos(2,1)),  // L 대칭 90
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(0,1), new Pos(0,2)),  // L 대칭 180
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(2,0), new Pos(2,1)), // L 대칭 270
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(1,1), new Pos(2,1)),  // ㄹ
                new Tetromino(new Pos(0,0), new Pos(0,-1), new Pos(1,-1), new Pos(1,-2)),  // ㄹ 90
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(1,-1), new Pos(2,-1)),  // ㄹ 대칭
                new Tetromino(new Pos(0,0), new Pos(0,1), new Pos(1,1), new Pos(1, 2)),  // ㄹ 대칭 90
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(2,0), new Pos(1,1)),  // ㅜ 
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(1,-1), new Pos(1,1)),  // ㅓ
                new Tetromino(new Pos(0,0), new Pos(1,0), new Pos(2,0), new Pos(2,-1)),  // ㅗ
                new Tetromino(new Pos(0,0), new Pos(0,-1), new Pos(0,1), new Pos(1,0))   // ㅏ
            };
            return tetrominos;
        }

        static int Solution(int n, int m, int[,] arr)
        {
            int ret = -1;

            Tetromino[] tetrominos = MakeTetromino();

            for (int y = 0; y < n; y++)
            {
                for (int x = 0; x < m; x++)
                {
                    for (int t = 0; t < tetrominos.Length; t++)
                    {
                        if (CheckBound(ref tetrominos[t], arr, out int value))
                            ret = Math.Max(ret, value);

                        if (x == m - 1)
                            tetrominos[t].Move(-(m - 1), 1);
                        else
                            tetrominos[t].Move(1, 0);
                    }
                }
            }
            return ret;
        }

        static void Main(string[] args)
        {
            string[] nm = Console.ReadLine().Split(' ');
            int n = int.Parse(nm[0]);
            int m = int.Parse(nm[1]);
            int[,] arr = new int[n, m];
            for (int i = 0; i < n; i++)
            {
                string[] str = Console.ReadLine().Split(' ');
                for (int j = 0; j < str.Length; j++)
                {
                    arr[i, j] = int.Parse(str[j]);
                }
            }

            Console.WriteLine(Solution(n, m, arr));
        }
    }
}