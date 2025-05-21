// 백준 2143번 : 두 배열의 합
// 시도 1. 부분 배열(n^2) * 이진 탐색(log(n)) = 10,000,000
//  -> 로직이 잘못됨.
// 시도 2. 부분 배열(n^2) * map.find(log(n))
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

typedef long long ll;

int t, n, m;
vector<int> a, b;

vector<int> GetSubArraySums(const vector<int>& arr)
{
	vector<int> result;
	for (int i = 0; i < arr.size(); i++)
	{
		int sum = 0;
		for (int j = i; j < arr.size(); j++)
		{
			sum += arr[j];
			result.push_back(sum);
		}
	}
	return result;
}

ll solve()
{
	unordered_map<int, int> aSumCounts;
	for (int aSum : GetSubArraySums(a))
		aSumCounts[aSum]++;

	map<int, int> bSumCounts;
	for (int bSum : GetSubArraySums(b))
		bSumCounts[bSum]++;

	ll pairCount = 0;
	for (auto iter = aSumCounts.begin(); iter != aSumCounts.end(); iter++)
	{
		int aSum = (*iter).first;
		int aSumCount = (*iter).second;

		// log(N)
		if (bSumCounts.find(t - aSum) != bSumCounts.end())
			pairCount += (ll)bSumCounts[t - aSum] * aSumCount;
	}

	return pairCount;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;

	cin >> n;
	a.assign(n, 0);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	cin >> m;
	b.assign(m, 0);
	for (int i = 0; i < m; i++)
		cin >> b[i];

	cout << solve() << '\n';

	return 0;
}

