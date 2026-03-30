#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(vector<int>& a, vector<int>& b)
{
    if (a[0] == b[0])
        return a[1] < b[1];
    return a[0] < b[0];
}

int solution(vector<vector<int>> routes) {
    int answer = 0;

    sort(routes.begin(), routes.end(), cmp);
    pair<int, int> cur;
    for (vector<int>& r : routes)
    {
        if (cur.second < r[0])
        {
            cur = { r[0], r[1] };
            answer++;
            continue;
        }

        cur = { r[0], min(r[1], cur.second) };
    }

    return answer;
}