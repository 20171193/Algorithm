#include<vector>
#include<algorithm>
using namespace std;

// 최소 높이, 최대 높이
typedef long long ll;

int high = -1, low = 1000'000'001;

// n 높이로 평탄화
ll Flatten(int n, const vector<vector<int>>& land, int P, int Q)
{
    ll ret = 0;
    ll diff = 0;
    for (const vector<int>& l : land)
    {
        for (int h : l)
        {
            diff = n - h;
            ret += (diff < 0 ? diff * -Q : diff * P);
        }
    }
    return ret;
}

long long solution(vector<vector<int>> land, int P, int Q) {
    long long answer = -1;

    for (const vector<int>& l : land)
    {
        for (int h : l)
        {
            high = max(h, high);
            low = min(h, low);
        }
    }

    while (low <= high)
    {
        int mid = (high + low) >> 1;

        ll qCost = Flatten(mid, land, P, Q);
        ll pCost = Flatten(mid + 1, land, P, Q);

        if (answer == -1)
            answer = min(qCost, pCost);
        else
            answer = min({ answer, qCost, pCost });

        // 제거
        if (qCost < pCost)
            high = mid - 1;
        // 추가
        else
            low = mid + 1;  
    }

    return answer;
}