using System.Runtime.CompilerServices;

namespace 백준5525번_IOIOI
{
    class Program
    {
        static int solution(int n, int m, string s)
        {
            int answer = 0;
            Stack<char> st = new Stack<char>();

            for (int i = 0; i < s.Length; i++)
            {
                if (st.Count == 0)
                {
                    if (s[i] == 'I')
                        st.Push(s[i]);
                }
                else
                {
                    if (st.Peek() == s[i])
                    {
                        while (st.Count > 0) st.Pop();

                        if (s[i] == 'I')
                            st.Push(s[i]);
                    }
                    else
                    {
                        if (s[i] == 'I' && st.Count == n * 2)
                        {
                            answer++;
                            // 끝에 IO 만 빼기
                            st.Pop();
                            st.Pop();
                        }
                        st.Push(s[i]);
                    }
                }
            }

            return answer;
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            int m = int.Parse(Console.ReadLine());
            string s = Console.ReadLine();

            Console.WriteLine(solution(n, m, s));
        }
    }

}