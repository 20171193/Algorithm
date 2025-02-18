using System;

namespace 백준17140번_이차원_배열과_연산
{
    class Program
    {
        enum Operation
        {
            R = 0,
            C = 1
        }

        static bool Check(int r, int c, int k, List<List<int>> arr)
        {
            if (arr.Count < r - 1 || arr[0].Count < c - 1)
                return false;

            return arr[r][c] == k;
        }

        // 시계방향 회전
        static void RotateCW(ref List<List<int>> matrix)
        {
            int row = matrix.Count;
            int col = matrix[0].Count;

            List<List<int>> tempMatrix = new List<List<int>>(col);
            for (int i = 0; i < col; i++)
                tempMatrix.Add(Enumerable.Repeat(0, row).ToList());

            for (int i = 0; i < row; i++)
                for (int j = 0; j < col; j++)
                    tempMatrix[j][row - 1 - i] = matrix[i][j];

            matrix = tempMatrix;
        }
        // 반시계방향 회전
        static void RotateCCW(ref List<List<int>> matrix)
        {
            int row = matrix.Count;
            int col = matrix[0].Count;

            List<List<int>> tempMatrix = new List<List<int>>(col);
            for (int i = 0; i < col; i++)
                tempMatrix.Add(Enumerable.Repeat(0, row).ToList());

            for (int i = 0; i < row; i++)
                for (int j = 0; j < col; j++)
                    tempMatrix[col - 1 - j][i] = matrix[i][j];

            matrix = tempMatrix;
        }

        static void Sort(Operation oper, ref List<List<int>> arr)
        {
            Dictionary<int, int> dic = new Dictionary<int, int>();
            int maxSize = 0;

            // 열 정렬 (행 / 열 뒤집기) 
            if (oper == Operation.C)
                RotateCW(ref arr);

            for (int i = 0; i < arr.Count; i++)
            {
                for (int j = 0; j < arr[i].Count; j++)
                {
                    int num = arr[i][j];
                    if (num == 0) break;

                    if (dic.ContainsKey(num))
                        dic[num]++;
                    else
                        dic[num] = 1;
                }
                var sortedDic = dic.OrderByDescending(p => p.Value).ToList();

                arr[i] = new List<int>(sortedDic.Count);
                maxSize = Math.Max(maxSize, arr[i].Count);
                foreach (var pair in sortedDic)
                {
                    arr[i].Add(pair.Key);
                    arr[i].Add(pair.Value);
                }
            }

            for (int i = 0; i < arr.Count; i++)
            {
                if (arr[i].Count < maxSize)
                    arr[i].AddRange(Enumerable.Repeat(0, maxSize - arr[i].Count));
            }

            // 열 정렬 (원복)
            if (oper == Operation.C)
                RotateCCW(ref arr);
        }

        static int solution(int r, int c, int k, List<List<int>> arr)
        {
            int answer = 0;
            int row = 3, col = 3;

            while (answer < 100 && !Check(r, c, k, arr))
            {
                answer++;
                row = arr.Count;
                col = arr[0].Count;

                // R : A의 모든 행에 대해서 정렬
                if (row >= col)
                    Sort(Operation.R, ref arr);
                // C : A의 모든 열에 대해서 정렬
                else
                    Sort(Operation.C, ref arr);
            }

            return answer;
        }

        static void Main(string[] args)
        {
            string[] rck = Console.ReadLine().Split(' ');
            int r = int.Parse(rck[0]);
            int c = int.Parse(rck[1]);
            int k = int.Parse(rck[2]);

            List<List<int>> list = new List<List<int>> { new List<int>(), new List<int>(), new List<int>() };
            for (int i = 0; i < 3; i++)
            {
                string[] temp = Console.ReadLine().Split(' ');
                for (int j = 0; j < 3; j++)
                    list[i].Add(int.Parse(temp[j]));
            }

            Console.WriteLine(solution(r, c, k, list));
        }
    }
}