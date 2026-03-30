#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

const int Calc(int a, int b, char oper)
{
    if (oper == '+') return a + b;
    if (oper == '-') return a - b;
    return 0;
}

int solution(vector<string> arr)
{
    int answer = -1;

    vector<int> num;
    vector<char> oper;

    for (int i = 0; i < arr.size(); i++)
    {
        if (i % 2 != 0)
            oper.push_back(arr[i][0]);
        else
            num.push_back(stoi(arr[i]));
    }

    // 구간합
    vector<vector<int>> pfxMinSum(num.size(), vector<int>(num.size())),
        pfxMaxSum(num.size(), vector<int>(num.size()));

    for (int i = 0; i < num.size(); i++)
        pfxMinSum[i][i] = pfxMaxSum[i][i] = num[i];

    for (int len = 2; len <= num.size(); len++)
    {
        for (int s = 0; s <= num.size() - len; s++)
        {
            int e = s + len - 1;

            pfxMinSum[s][e] = INT_MAX;
            pfxMaxSum[s][e] = INT_MIN;

            for (int p = s; p < e; p++)
            {
                int mnLeft = pfxMinSum[s][p];
                int mxLeft = pfxMaxSum[s][p];
                int mnRight = pfxMinSum[p + 1][e];
                int mxRight = pfxMaxSum[p + 1][e];

                // 가능한 모든 연산 실행
                int a = Calc(mnLeft, mnRight, oper[p]);
                int b = Calc(mnLeft, mxRight, oper[p]);
                int c = Calc(mxLeft, mnRight, oper[p]);
                int d = Calc(mxLeft, mxRight, oper[p]);

                pfxMinSum[s][e] = min(pfxMinSum[s][e], min({ a,b,c,d }));
                pfxMaxSum[s][e] = max(pfxMaxSum[s][e], max({ a,b,c,d }));
            }
        }
    }

    answer = pfxMaxSum[0][num.size() - 1];
    return answer;
}