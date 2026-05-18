// 프로그래머스(L2) : 큰 수 만들기
// 조건
// 1. 주어진 문자열에서 K만큼의 수를 제거해서
//    만들 수 있는 수 중 가장 큰 수 return
// 2. 순서는 그대로
// 풀이
// 1. number의 길이는 최대 1,000,000 => 완탐 불가
// 2. 상단 갱신 : 유사 스택
using System;

public class Solution
{
    public static string solution(string number, int k)
    {
        int length = number.Length;
        char[] answer = new char[length];

        answer[0] = number[0];

        int top = 0;
        for(int i = 1; i<number.Length; i++)
        {
            while(k > 0 && top >= 0 && answer[top] < number[i])
            {
                top--;
                k--;
            }

            answer[++top] = number[i];
        }

        return new string(answer, 0, length - k);
    }

    public static void Main(string[] args)
    {
        Console.WriteLine(solution("4177252841", 4));
    }
}
