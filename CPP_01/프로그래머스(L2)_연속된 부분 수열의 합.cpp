#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer;
    int s = 0, sum = 0, minDist = sequence.size() + 1;

    for (int i = 0; i < sequence.size(); i++)
    {
        sum += sequence[i];

        while (sum > k)
            sum -= sequence[s++];

        if (sum == k)
        {
            if (minDist > i - s)
            {
                minDist = i - s;
                answer = { s, i };
            }
            sum -= sequence[s++];
        }
    }

    return answer;
}