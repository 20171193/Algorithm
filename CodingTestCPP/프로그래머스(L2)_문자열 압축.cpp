#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

int solution(string s) {
    int answer = s.size();

    int base = s.size() / 2;
    while (base > 0)
    {
        int length = 0;
        string prev = s.substr(0, base);
        int count = 1;

        for (int i = base; i < s.size(); i += base)
        {
            string cur = s.substr(i, base);
            if (prev == cur)
                count++;
            else
            {
                if (count > 1)
                {
                    length += base + log10(count) + 1;
                    count = 1;
                }
                else
                    length += prev.size();
                prev = cur;
            }
        }

        if (count > 1)
            length += base + log10(count) + 1;
        else
            length += prev.size();

        answer = min(answer, length);
        base--;
    }

    return answer;
}