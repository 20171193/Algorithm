using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace CodingTestCsharp.백준
{
    // 1. n*m
    // 2. 4방향
    // 3. 방문체크
    class 백준21736번_헌내기는_친구가_필요해
    {
        public struct Pos
        {
            public int y, x; 
            public Pos(int y, int x)
            {
                this.y = y; this.x = x;
            }
            public static Pos operator +(Pos a, Pos b)
            {
                return new Pos(a.y + b.y, a.x + b.x);
            }
        }

        public static Pos[] directions = { new Pos(1, 0), new Pos(-1, 0), new Pos(0, 1), new Pos(0, -1) };

        static int solution(int n, int m, string[] arr)
        {
            Queue<Pos> q = new Queue<Pos>();
            bool[,] visited = new bool[n, m];

            int result = 0;

            for(int y = 0; y< n; y++)
            {
                for(int x = 0; x< m; x++)
                {
                    if(arr[y][x] == 'I')
                    {
                        q.Enqueue(new Pos(y, x));
                        visited[y, x] = true;
                        break;
                    }
                }
            }

            while(q.Count > 0 )
            {
                Pos cur = q.Dequeue();
                for(int i =0;i <4; i++)
                {
                    Pos nPos = cur + directions[i];
                    if (nPos.y < 0 || nPos.y >= n || nPos.x < 0 || nPos.x >= m) continue;
                    if (arr[nPos.y][nPos.x] == 'X') continue;
                    if (visited[nPos.y, nPos.x]) continue;
                    if (arr[nPos.y][nPos.x] == 'P') result++;

                    q.Enqueue(nPos);
                    visited[nPos.y, nPos.x] = true;
                }
            }
            return result;
        }

        static void Main(string[] args)
        {
            string[] nm = Console.ReadLine().Split(' ');
            int n = int.Parse(nm[0]);
            int m = int.Parse(nm[1]);
            
            string[] arr = new string[n];
            for(int i =0; i<n; i++)
                arr[i] = Console.ReadLine();

            Console.WriteLine(solution(n, m, arr));
        }

    }
}
