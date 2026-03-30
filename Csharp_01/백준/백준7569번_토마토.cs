namespace 백준7569번_토마토
{
    class Program
    {
        struct Direction
        {
            public int x, y, h;

            public static Direction operator +(Direction d1, Direction d2)
            {
                return new Direction(d1.x + d2.x, d1.y + d2.y, d1.h + d2.h);
            }
            public Direction(int x, int y, int h)
            {
                this.x = x;
                this.y = y;
                this.h = h;
            }
        }

        static bool CheckBound(int x, int y, int h, Direction targetPos)
        {
            if (targetPos.x < 0 || targetPos.x >= x) return false;
            if (targetPos.y < 0 || targetPos.y >= y) return false;
            if (targetPos.h < 0 || targetPos.h >= h) return false;
            return true;
        }

        static int solution(int m, int n, int h, int[,,] boxes)
        {
            int tmtCount = 0;
            int dayCount = 0;
            Direction[] dirs =
                {
                new Direction(0,0,1), new Direction(0,0,-1),    // 위, 아래
                new Direction(0,1,0), new Direction(0,-1,0),    // 앞, 뒤
                new Direction(1,0,0), new Direction(-1,0,0)     // 우, 좌
            };

            Queue<Direction> q = new Queue<Direction>();

            // 최초에 익은 토마토 담기 (탐색을 시작할 좌표)
            for (int _h = 0; _h < h; _h++)
            {
                for (int y = 0; y < n; y++)
                {
                    for (int x = 0; x < m; x++)
                    {
                        if (boxes[_h, y, x] == 1)
                        {
                            q.Enqueue(new Direction(x, y, _h));
                            tmtCount++;
                        }
                    }
                }
            }

            while (q.Count > 0)
            {
                Direction cur = q.Dequeue();
                tmtCount--;

                for (int i = 0; i < 6; i++)
                {
                    Direction next = cur + dirs[i];
                    // 범위 내 존재하는 위치인지 
                    if (!CheckBound(m, n, h, next))
                        continue;
                    // 익지 않은 토마토인지
                    if (boxes[next.h, next.y, next.x] != 0)
                        continue;

                    boxes[next.h, next.y, next.x] = 1;
                    q.Enqueue(next);
                }

                // 현재 깊이의 익은 토마토들을 모두 확인한 경우
                if (tmtCount == 0)
                {
                    // 날짜 카운트
                    dayCount++;
                    tmtCount = q.Count;
                }
            }

            // 모든 토마토가 익었는지 확인
            for (int _h = 0; _h < h; _h++)
            {
                for (int y = 0; y < n; y++)
                {
                    for (int x = 0; x < m; x++)
                    {
                        if (boxes[_h, y, x] == 0)
                            return -1;
                    }
                }
            }

            return dayCount - 1;
        }

        static void Main(string[] args)
        {
            int[] mnh = Console.ReadLine().Split(" ").Select(int.Parse).ToArray();

            int[,,] boxes = new int[mnh[2], mnh[1], mnh[0]];
            for (int h = 0; h < mnh[2]; h++)
            {
                for (int y = 0; y < mnh[1]; y++)
                {
                    int[] arr = Console.ReadLine().Split(" ").Select(int.Parse).ToArray();
                    for (int x = 0; x < mnh[0]; x++)
                    {
                        boxes[h, y, x] = arr[x];
                    }
                }
            }

            Console.WriteLine(solution(mnh[0], mnh[1], mnh[2], boxes));
        }
    }
}