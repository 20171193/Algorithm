#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer(2);

    unordered_set<string> set(gems.begin(), gems.end());
    int typeCount = set.size();
    int start = 0, end = 0;

    // 최대 길이 ~100,000
    int len = 100001;

    unordered_map<string, int> gemCount;

    // 투포인터
    while (end < gems.size())
    {
        gemCount[gems[end]]++;
        end++;

        while (gemCount.size() == typeCount)
        {
            if (end - start < len)
            {
                len = end - start;
                // start : 인덱스 + 1
                answer = { start + 1, end };
            }

            gemCount[gems[start]]--;

            if (gemCount[gems[start]] < 1)
                gemCount.erase(gems[start]);
            start++;
        }
    }

    return answer;
}