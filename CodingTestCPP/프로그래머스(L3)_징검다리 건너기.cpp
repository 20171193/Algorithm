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
            // ������� �� ���� ī����
            cnt++;
            
            // ������ ���̴� �ǳʷ��� ����� ��-1 �� �����Ǿ����.
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
    
    // �ٸ� ���� �������� �̺�Ž�� (ū ����)
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