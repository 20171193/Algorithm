#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int GetPalindrome(const string& str, int leftIdx, int rightIdx)
{
    while (leftIdx >= 0 && rightIdx < str.size() && str[leftIdx] == str[rightIdx])
    {
        leftIdx--;
        rightIdx++;
    }

    return rightIdx - leftIdx - 1;
}

int solution(string s)
{
    int answer = 1;

    for (int i = 0; i < s.size(); i++)
        // È¦/Â¦ ÆÓ¸°µå·Ò °í·Á
        answer = max({ answer, GetPalindrome(s, i, i), GetPalindrome(s,i,i + 1) });


    return answer;
}