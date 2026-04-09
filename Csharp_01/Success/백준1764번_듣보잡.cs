using System;

namespace 백준1764번_듣보잡
{
    class Program
    {
        static List<string> solution(string[] mainArr, string[] subArr)
        {
            List<string> answer = new List<string>();

            // unordered_set
            HashSet<string> hashSet = new HashSet<string>();

            for (int i = 0; i < mainArr.Length; i++)
                hashSet.Add(mainArr[i]);

            for (int i = 0; i < subArr.Length; i++)
                if (hashSet.Contains(subArr[i]))
                    answer.Add(subArr[i]);

            answer.Sort();

            return answer;
        }

        static void Main(string[] args)
        {
            int n = 0, m = 0;
            string[] nm = Console.ReadLine().Split(' ');
            n = int.Parse(nm[0]);
            m = int.Parse(nm[1]);

            string[] nPeps = new string[n];
            for (int i = 0; i < n; i++)
                nPeps[i] = Console.ReadLine();

            string[] mPeps = new string[m];
            for (int i = 0; i < m; i++)
                mPeps[i] = Console.ReadLine();

            // 1. 요소가 더 많은 배열을 기준 배열로 해시에 할당
            // 2. 요소가 적은 배열을 순회하며 해시에 요소가 존재하는지 확인
            List<string> answers = n > m ? solution(nPeps, mPeps) : solution(mPeps, nPeps);

            Console.WriteLine(answers.Count);
            foreach (string name in answers)
            {
                Console.WriteLine(name);
            }
        }
    }
}