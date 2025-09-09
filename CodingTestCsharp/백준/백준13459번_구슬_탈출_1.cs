using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

namespace 백준13459번_구슬_탈출_1
{
    public class Solution
    {
        public struct Pos
        {
            public int y, x;
            public Pos(int y, int x) { this.y = y; this.x = x; }
            public static Pos Zero { get { return new Pos(0, 0); } }
            public static Pos operator +(Pos a, Pos b) { return new Pos(a.y + b.y, a.x + b.x); }
            public static Pos operator -(Pos a, Pos b) { return new Pos(a.y - b.y, a.x - b.x); }
            public static bool operator ==(Pos a, Pos b) { return a.y == b.y && a.x == b.x; }
            public static bool operator !=(Pos a, Pos b) { return a.y != b.y || a.x != b.x; }
        }
        static Pos[] directions = { new Pos(0, 1), new Pos(0, -1), new Pos(1, 0), new Pos(-1, 0) };
        static int n = 0, m = 0;
        static char[,] arr;

        public struct BeadInfo
        {
            public int moveCount;
            public Pos redPos, bluePos;
            public BeadInfo(Pos redPos, Pos bluePos, int moveCount) { this.redPos = redPos; this.bluePos = bluePos; this.moveCount = moveCount; }
        }

        static Pos Move(Pos originPos, Pos otherPos, int dir)
        {
            Pos nextPos = originPos + directions[dir];
            while (true)
            {
                char nextInfo = arr[nextPos.y, nextPos.x];

                if (nextInfo == 'O')
                    return nextPos;
                else if (nextInfo == '#' || nextPos == otherPos)
                    break;
                nextPos += directions[dir];
            }
            return nextPos - directions[dir];
        }

        static int Solve()
        {
            Pos rp = Pos.Zero, bp = Pos.Zero;
            bool findBeadFlag = false;
            for (int y = 1; y < arr.GetLength(0) - 1; y++)
            {
                for (int x = 1; x < arr.GetLength(1) - 1; x++)
                {
                    if (arr[y, x] == 'R')
                    {
                        rp = new Pos(y, x);
                        arr[y, x] = '.';
                    }
                    else if (arr[y, x] == 'B')
                    {
                        bp = new Pos(y, x);
                        arr[y, x] = '.';
                    }

                    if (rp != Pos.Zero && bp != Pos.Zero)
                    {
                        findBeadFlag = true;
                        break;
                    }
                }
                if (findBeadFlag)
                    break;
            }

            // BFS
            Queue<BeadInfo> q = new Queue<BeadInfo>();
            q.Enqueue(new BeadInfo(rp, bp, 0));

            while (q.Count > 0)
            {
                BeadInfo cur = q.Dequeue();

                for (int d = 0; d < 4; d++)
                {
                    Pos nrp = new Pos(), nbp = new Pos();

                    // 같은 축 판별
                    //  d<2 : x축 이동
                    // d>=2 : y축 이동
                    if ((d < 2 && (cur.redPos.y == cur.bluePos.y))
                        || d >= 2 && (cur.redPos.x == cur.bluePos.x))
                    {
                        switch (d)
                        {
                            case 0:
                                {
                                    if (cur.redPos.x > cur.bluePos.x)
                                    {
                                        nrp = Move(cur.redPos, cur.bluePos, d);
                                        nbp = Move(cur.bluePos, nrp, d);
                                    }
                                    else
                                    {
                                        nbp = Move(cur.bluePos, cur.redPos, d);
                                        nrp = Move(cur.redPos, nbp, d);
                                    }
                                    break;
                                }
                            case 1:
                                {
                                    if (cur.redPos.x < cur.bluePos.x)
                                    {
                                        nrp = Move(cur.redPos, cur.bluePos, d);
                                        nbp = Move(cur.bluePos, nrp, d);
                                    }
                                    else
                                    {
                                        nbp = Move(cur.bluePos, cur.redPos, d);
                                        nrp = Move(cur.redPos, nbp, d);
                                    }
                                    break;
                                }
                            case 2:
                                {
                                    if (cur.redPos.y > cur.bluePos.y)
                                    {
                                        nrp = Move(cur.redPos, cur.bluePos, d);
                                        nbp = Move(cur.bluePos, nrp, d);
                                    }
                                    else
                                    {
                                        nbp = Move(cur.bluePos, cur.redPos, d);
                                        nrp = Move(cur.redPos, nbp, d);
                                    }
                                    break;
                                }
                            case 3:
                                {
                                    if (cur.redPos.y < cur.bluePos.y)
                                    {
                                        nrp = Move(cur.redPos, cur.bluePos, d);
                                        nbp = Move(cur.bluePos, nrp, d);
                                    }
                                    else
                                    {
                                        nbp = Move(cur.bluePos, cur.redPos, d);
                                        nrp = Move(cur.redPos, nbp, d);
                                    }
                                    break;
                                }
                            default:
                                break;
                        }
                    }
                    else
                    {
                        nbp = Move(cur.bluePos, cur.redPos, d);
                        nrp = Move(cur.redPos, nbp, d);
                    }

                    if (arr[nbp.y, nbp.x] == 'O' || cur.moveCount >= 10)
                        continue;
                    else if (arr[nrp.y, nrp.x] == 'O')
                        return 1;

                    q.Enqueue(new BeadInfo(nrp, nbp, cur.moveCount + 1));
                }
            }

            return 0;
        }

        static void Main(string[] args)
        {
            // input
            string[] nm = Console.ReadLine().Split(' ');
            n = int.Parse(nm[0]);
            m = int.Parse(nm[1]);

            arr = new char[n, m];
            for (int i = 0; i < n; i++)
            {
                string str = Console.ReadLine();
                for (int j = 0; j < str.Length; j++)
                {
                    arr[i, j] = str[j];
                }
            }

            // output
            Console.WriteLine(Solve());
        }
    }
}
