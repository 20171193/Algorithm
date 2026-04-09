using System;

namespace 기본_정렬문제_퀘스트_진행
{
    class Program
    {
        static int solution(List<int[]> quests)
        {
            int answer = 0;

            quests.Sort((a, b) =>
            {
                if (a[0] == b[0])
                    return b[1].CompareTo(a[1]);
                else
                    return a[0].CompareTo(b[0]);
            });


            int curExp = 0;
            foreach (int[] quest in quests)
            {
                if (curExp < quest[0])
                    break;

                curExp += quest[1];
                answer++;
            }

            return answer;
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());

            List<int[]> quests = new List<int[]>();

            for (int i = 0; i < n; i++)
            {
                string[] se = Console.ReadLine().Split(' ');
                quests.Add(new int[2] { int.Parse(se[0]), int.Parse(se[1]) });
            }

            Console.WriteLine(solution(quests));
        }
    }
}