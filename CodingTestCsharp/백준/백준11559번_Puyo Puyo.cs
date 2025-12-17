using System;
using System.Collections.Generic;

namespace CodingTestCsharp
{
    // 백준 11559번 : Puyo Puyo (https://www.acmicpc.net/problem/11559)
    //
    // 조건 
    // 1. 4개 이상의 블럭 발견 시 연쇄 카운팅
    //  1-1. 동시에 발견한 그룹은 한 번만 카운팅
    //
    // 풀이
    // 1. 같은 블럭 탐색(BFS)
    // 2. 제거 후 시프트는 제거된 열만
    // 3. 흐름 : 탐색 -> 제거 -> 시프트
    //
    class 백준11559번_PuyoPuyo
    {
        const int BOARD_HEIGHT = 12, BOARD_WIDTH = 6, ASCII_MAX = 128;

        static int[] imap = new int[ASCII_MAX];
        static char[] cmap = { '.', 'R', 'G', 'B', 'P', 'Y' };
        static int[,] board = new int[BOARD_HEIGHT, BOARD_WIDTH];
        public struct Pos
        {
            public int y, x;
            public Pos(int y, int x) { this.y = y; this.x = x; }
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
        }

        public static readonly Pos[] directions = { new Pos(1, 0), new Pos(-1, 0), new Pos(0, 1), new Pos(0, -1) };

        static bool BFS(Queue<Pos> q, Pos start, bool[,] visited, List<Pos> blocks)
        {
            List<Pos> findBlocks = new List<Pos>();
            int type = board[start.y, start.x];

            q.Enqueue(start);
            visited[start.y, start.x] = true;
            findBlocks.Add(start);

            while (q.Count > 0)
            {
                Pos cur = q.Dequeue();
                for (int d = 0; d < directions.Length; d++)
                {
                    Pos next = cur + directions[d];
                    if (next.y >= BOARD_HEIGHT || next.y < 0 || next.x >= BOARD_WIDTH || next.x < 0) continue;
                    if (visited[next.y, next.x]) continue;
                    if (board[next.y, next.x] != type) continue;

                    findBlocks.Add(next);
                    visited[next.y, next.x] = true;
                    q.Enqueue(next);
                }
            }

            if (findBlocks.Count >= 4)
            {
                foreach (Pos pos in findBlocks)
                    blocks.Add(pos);
                return true;
            }

            return false;
        }

        static void Shift(int col)
        {
            int bottom = -1;
            for (int row = BOARD_HEIGHT - 1; row >= 0; row--)
            {
                // 할당할 행 찾기 (블럭 사이 빈 공간은 없음)
                if (bottom == -1 && board[row, col] == 0)
                    bottom = row;

                // 블럭 옮기기 
                if (bottom != -1 && board[row, col] != 0)
                {
                    int temp = board[row, col];
                    board[row, col] = 0;
                    board[bottom--, col] = temp;
                }
            }
        }

        static int solution()
        {
            int answer = 0;

            // 1. BFS 연쇄 탐색
            Queue<Pos> q = new Queue<Pos>();
            bool[,] visited = new bool[BOARD_HEIGHT, BOARD_WIDTH];

            bool findFlag = true;
            List<Pos> blocks = new List<Pos>();

            while (findFlag)
            {
                findFlag = false;
                for (int row = BOARD_HEIGHT - 1; row >= 0; row--)
                {
                    bool rowEmptyFlag = true;
                    for (int col = 0; col < BOARD_WIDTH; col++)
                    {
                        if (board[row, col] == 0) continue;

                        rowEmptyFlag = false;
                        if (visited[row, col]) continue;
                        if (BFS(q, new Pos(row, col), visited, blocks))
                            findFlag = true;
                    }

                    // 현재 행이 아예 비어있는 경우 이후 탐색x
                    if (rowEmptyFlag) break;
                }

                // 2. 블록 제거 및 시프트
                if (findFlag)
                {
                    bool[] shiftCol = new bool[BOARD_WIDTH];
                    // 블록 제거
                    foreach (Pos pos in blocks)
                    {
                        board[pos.y, pos.x] = 0;
                        shiftCol[pos.x] = true;
                    }
                    // 시프트
                    for (int col = 0; col < BOARD_WIDTH; col++)
                    {
                        if (shiftCol[col])
                            Shift(col);
                    }

                    // 배열 초기화
                    blocks.Clear();
                    visited = new bool[BOARD_HEIGHT, BOARD_WIDTH];
                    answer++;
                }
            }

            return answer;
        }

        static void Main(string[] args)
        {
            // 조건 매핑 ".RGBPY"
            for (int i = 0; i < cmap.Length; i++)
                imap[cmap[i]] = i;

            string temp;
            for (int i = 0; i < BOARD_HEIGHT; i++)
            {
                temp = Console.ReadLine();
                for (int j = 0; j < BOARD_WIDTH; j++)
                {
                    board[i, j] = imap[temp[j]];
                }
            }

            Console.WriteLine(solution());
        }
    }
}
