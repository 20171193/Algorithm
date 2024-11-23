using System;
using System.Text;
namespace 백준1918번_후위_표기식
{
    class Program
    {
        static string Postfix(ref string infix)
        {
            StringBuilder postfix = new StringBuilder();
            Stack<char> opers = new Stack<char>();  // 연산자 스택

            for (int i = 0; i < infix.Length; i++)
            {
                // 피연산자 
                if (infix[i] >= 'A' && infix[i] <= 'Z')
                    postfix.Append(infix[i]);
                // 연산자
                else
                {
                    if (opers.Count < 1)
                        opers.Push(infix[i]);
                    else
                    {
                        if (infix[i] == ')')
                        {
                            while (opers.Peek() != '(')
                                postfix.Append(opers.Pop());
                            opers.Pop();    // '(' pop
                        }
                        else if (infix[i] == '(')
                            opers.Push(infix[i]);
                        else
                        {
                            switch (opers.Peek())
                            {
                                case '*':
                                case '/':
                                    {
                                        if (infix[i] == '+' || infix[i] == '-')
                                        {
                                            while (opers.Count > 0 && opers.Peek() != '(')
                                                postfix.Append(opers.Pop());
                                        }
                                        else if (infix[i] == '*' || infix[i] == '/')
                                            postfix.Append(opers.Pop());

                                        break;
                                    }
                                case '+':
                                case '-':
                                    {
                                        if (infix[i] == '+' || infix[i] == '-')
                                            postfix.Append(opers.Pop());
                                        break;
                                    }
                                default:
                                    break;
                            }
                            opers.Push(infix[i]);
                        }
                    }
                }

            }

            while (opers.Count > 0)
                postfix.Append(opers.Pop());

            return postfix.ToString();
        }

        static void Main(string[] args)
        {
            string infix = Console.ReadLine();
            Console.WriteLine(Postfix(ref infix));
        }
    }
}