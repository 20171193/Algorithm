#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
typedef long long ll;

using namespace std;
// 동적으로 루트 할당(최대 400,000)
unordered_map<ll, ll> rootMap;

ll Find(const ll& num)
{
    if (rootMap.find(num) == rootMap.end())
        rootMap.insert({ num,num });

    if (rootMap[num] != num)
        rootMap[num] = Find(rootMap[num]);

    return rootMap[num];
}

void Union(const ll& child, const ll& parent)
{
    ll parentRoot = Find(parent);
    rootMap[child] = parentRoot;
}

vector<ll> solution(ll k, vector<ll> room_number) {
    vector<ll> answer;

    for (int i = 0; i < room_number.size(); i++)
    {
        ll& num = room_number[i];

        num = Find(num);
        answer.push_back(num);

        if (num < k)
            Union(num, num + 1);
    }

    return answer;
}