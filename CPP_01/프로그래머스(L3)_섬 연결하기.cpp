#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int root[101];

bool cmp(vector<int>& a, vector<int>& b)
{
    if (a[2] == b[2])
        return a[0] < b[0];
    else
        return a[2] < b[2];
}


int Find(int s)
{
    if (root[s] != s)
        root[s] = Find(root[s]);

    return root[s];
}

int MakeMST(vector<vector<int>>& edges)
{
    int ret = 0;
    for (vector<int>& edge : edges)
    {
        int s = edge[0];
        int e = edge[1];
        int v = edge[2];

        int rootS = Find(s);
        int rootE = Find(e);

        if (rootS != rootE)
        {
            root[rootS] = rootS > rootE ? rootS : rootE;
            root[rootE] = rootS > rootE ? rootS : rootE;
            ret += v;
        }
    }
    return ret;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    sort(costs.begin(), costs.end(), cmp);
    for (int i = 0; i < n; i++)
    {
        root[i] = i;
    }
    answer = MakeMST(costs);

    return answer;
}
