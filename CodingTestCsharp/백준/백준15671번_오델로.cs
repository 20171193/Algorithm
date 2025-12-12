using System;
using System.ComponentModel.Design;
using System.Numerics;
using System.Reflection.Metadata.Ecma335;
using System.Reflection.PortableExecutable;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace CodingTestCsharp.백준
{
    // 백준 15671번 : 오델로 (https://www.acmicpc.net/problem/15671)
    // 풀이
    // 1. 돌을 둔 위치에서 조건 탐색

    // 시도
    // 1. 실패(컴파일러 환경에 따라 개행 문자열 길이가 다름;)
    //  - Environment.NewLine.Length (현재 버전의 개행 문자열 길이 확인)
    class 백준15671_오델로
    {
        public const int BOARD_SIZE = 6, BLANK = 0, WHITE = 1, BLACK = -1;
        static int n;
        static int[,] board = new int[BOARD_SIZE + 1, BOARD_SIZE + 1];
        static Pos[] turns;

        public struct Pos
        {
            public readonly int y;
            public readonly int x;
            public Pos(int y, int x) { this.y = y; this.x = x; }

            public static readonly Pos[] directions = { new Pos(-1, -1), new Pos(0, -1), new Pos(1, -1), new Pos(1, 0), new Pos(-1, 0), new Pos(-1, 1), new Pos(0, 1), new Pos(1, 1) };
            public static Pos operator +(Pos a, Pos b)
            {
                return new Pos(a.y + b.y, a.x + b.x);
            }
            public static Pos operator -(Pos a, Pos b)
            {
                return new Pos(a.y - b.y, a.x - b.x);
            }
            public static bool operator ==(Pos a, Pos b)
            {
                return a.y == b.y && a.x == b.x;
            }
            public static bool operator !=(Pos a, Pos b)
            {
                return a.y != b.y || a.x != b.x;
            }

            public bool CheckBound(int minBound, int maxBound) { return y >= minBound && y <= maxBound && x >= minBound && x <= maxBound; }
        }

        static void Place(Pos pos, int curTurn)
        {
            int oppTurn = -curTurn;
            board[pos.y, pos.x] = curTurn;

            for (int d = 0; d < 8; d++)
            {
                Pos curPos = pos;

                bool canFlip = false;
                int oppCnt = 0;
                // 뒤집을 수 있는지 확인
                while (!canFlip)
                {
                    curPos += Pos.directions[d];

                    if (!curPos.CheckBound(1, BOARD_SIZE)) break;
                    if (board[curPos.y, curPos.x] == curTurn)
                    {
                        if (oppCnt > 0)
                            canFlip = true;
                        break;
                    }
                    if (board[curPos.y, curPos.x] != oppTurn) break;
                    oppCnt++;
                }

                // 뒤집기 
                if (canFlip)
                {
                    while (curPos != pos)
                    {
                        curPos -= Pos.directions[d];
                        board[curPos.y, curPos.x] = curTurn;
                    }
                }
            }
        }
        public static void solution()
        {
            // 초기 보드 세팅
            board[3, 3] = board[4, 4] = WHITE;
            board[3, 4] = board[4, 3] = BLACK;

            // 모든 턴 시뮬레이션 
            for (int i = 0; i < n; i++)
            {
                int curTurn = i % 2 == 0 ? BLACK : WHITE;
                Place(turns[i], curTurn);
            }

            // format, output
            StringBuilder strBoard = new StringBuilder();
            int wCnt = 0, bCnt = 0;

            // 개행 길이 카운팅
            int newLineLength = Environment.NewLine.Length;
            for (int y = 1; y <= BOARD_SIZE; y++)
            {
                strBoard.AppendLine("......");

                for (int x = 1; x <= BOARD_SIZE; x++)
                {
                    if (board[y, x] != BLANK)
                    {
                        // 열 개수 = BOARD_SIZE + 2('\r', '\n')
                        // 수정 시도 Environment.NewLine.Length
                        int buliderIndex = ((y - 1) * (BOARD_SIZE + newLineLength) + x - 1);
                        if (board[y, x] == WHITE)
                        {
                            wCnt++;
                            strBoard[buliderIndex] = 'W';
                        }
                        else // BLACK
                        {
                            bCnt++;
                            strBoard[buliderIndex] = 'B';
                        }
                    }
                }
            }
            Console.Write(strBoard.ToString());
            if (wCnt > bCnt)
                Console.WriteLine("White");
            else
                Console.WriteLine("Black");
        }

        static void Main(string[] args)
        {
            n = int.Parse(Console.ReadLine());
            turns = new Pos[n];
            int y = 0, x = 0;
            string[] yx = null;
            for (int i = 0; i < n; i++)
            {
                yx = Console.ReadLine().Split();
                y = int.Parse(yx[0]);
                x = int.Parse(yx[1]);
                turns[i] = new Pos(y, x);
            }

            solution();
        }
    }
}
