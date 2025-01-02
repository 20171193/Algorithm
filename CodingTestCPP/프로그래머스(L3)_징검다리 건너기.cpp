#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool Check(int k, int stone, vector<int>& stones)
{
    int cnt = 0;
    for (int i = 0; i < stones.size(); i++)
    {
        if (stones[i] <= stone)
        {
            // 사라지는 돌 개수 카운팅
            cnt++;
            
            // 끊어진 길이는 건너려는 사람의 수-1 이 충족되어야함.
            if (cnt == k)
                return false;
        }
        else
            cnt = 0;
    }
    return true;
}

int solution(vector<int> stones, int k) {
    int left = 0, mid = 0;
    int right = *max_element(stones.begin(), stones.end());
    
    // 다리 숫자 기준으로 이분탐색 (큰 범위)
    while (left <= right)
    {
        mid = (left + right) >> 1;

        if (Check(k, mid, stones))
            left = mid + 1;
        else
            right = mid - 1;
    }

    return left;
}