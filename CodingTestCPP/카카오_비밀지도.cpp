// 2017 īī�� ���� ��ä 1��
// 1. ������� 

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string GetString(int n, int bit)
{
    string ret;

    while (n--)
    {
        if (bit > 0)
        {
            ret += bit % 2 ? "#" : " ";
            bit /= 2;
        }
        else
            ret += " ";
    }

    reverse(ret.begin(), ret.end());
    return ret;
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;

    for (int i = 0; i < n; i++)
    {
        int bit = arr1[i] | arr2[i];
        answer.push_back(GetString(n, bit));
    }
    return answer;
}