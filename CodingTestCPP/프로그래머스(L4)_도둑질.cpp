#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> money) {
    vector<int> frontDP(money.size()), backDP(money.size());

    // 첫번째 집부터
    frontDP[0] = money[0];
    frontDP[1] = max(money[0], money[1]);

    // 두번째 집부터
    backDP[0] = 0;
    backDP[1] = money[1];

    for (int i = 2; i < money.size(); i++)
    {
        // 첫번째 집은 마지막 집 제외
        if (i < money.size() - 1)
            frontDP[i] = max(frontDP[i - 2] + money[i], frontDP[i - 1]);

        backDP[i] = max(backDP[i - 2] + money[i], backDP[i - 1]);
    }

    return max(frontDP[money.size() - 2], backDP[money.size() - 1]);
}