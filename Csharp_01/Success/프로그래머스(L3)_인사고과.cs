using System;
using System.Collections.Generic;
using System.Reflection;

namespace 프로그래머스L3_인사고과
{
    public class Solution
    {
        public struct Pair
        {
            public int Item1 { get; }
            public int Item2 { get; }
            public Pair(int Item1, int Item2)
            {
                this.Item1 = Item1;
                this.Item2 = Item2;
            }
        }

        public int solution(int[,] scores)
        {
            int answer = 1;

            List<List<int>> list = new List<List<int>>();
            for (int i = 0; i < scores.GetLength(0); i++)
            {
                List<int> row = new List<int>() { scores[i, 0], scores[i, 1], i };
                list.Add(row);
            }

            list.Sort((x, y) => x[0] == y[0] ? x[1].CompareTo(y[1]) : y[0].CompareTo(x[0]));

            List<Pair> orders = new List<Pair>();
            orders.Add(new Pair(list[0][0] + list[0][1], list[0][2]));
            Pair maxScore = new Pair(list[0][0], list[0][1]);
            for (int i = 1; i < list.Count; i++)
            {
                if (maxScore.Item2 < list[i][1])
                {
                    maxScore = new Pair(list[i][0], list[i][1]);
                }
                else if (maxScore.Item2 > list[i][1] && maxScore.Item1 != list[i][0])
                {
                    if (list[i][2] == 0)
                        return -1;
                    continue;
                }

                orders.Add(new Pair(list[i][0] + list[i][1], list[i][2]));
            }

            orders.Sort((a, b) => a.Item1 == b.Item1 ? a.Item2.CompareTo(b.Item2) : b.Item1.CompareTo(a.Item1));
            int prevScore = int.MaxValue;

            for (int i = 0; i < orders.Count; i++)
            {
                if (prevScore > orders[i].Item1)
                {
                    answer = i + 1;
                    prevScore = orders[i].Item1;
                }
                if (orders[i].Item2 == 0)
                    break;
            }

            return answer;
        }
    }
}