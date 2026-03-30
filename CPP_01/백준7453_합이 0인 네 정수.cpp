// 백준 7453번 : 합이 0인 네 정수
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int n, a[4001], b[4001], c[4001], d[4001];

ll solution()
{
	ll answer = 0;

	vector<ll> ab, cd;
	int size = n * n;
	ab.reserve(size);
	cd.reserve(size);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ab.push_back(a[i] + b[j]);
			cd.push_back(c[i] + d[j]);
		}
	}

	sort(ab.begin(), ab.end());
	sort(cd.begin(), cd.end());

	int left = 0, right = size - 1;
	while (left < size && right >= 0)
	{
		ll sum = ab[left] + cd[right];

		if (sum == 0)
		{
			ll leftVal = ab[left], rightVal = cd[right];
			int leftCount = 0, rightCount = 0;
			while (left < size && ab[left] == leftVal)
			{
				leftCount++;
				left++;
			}
			while (right >= 0 && cd[right] == rightVal)
			{
				rightCount++;
				right--;
			}

			answer += (ll)leftCount * rightCount;
		}
		else if (sum > 0)
			right--;
		else
			left++;
	}
	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i] >> b[i] >> c[i] >> d[i];

	cout << solution();
	return 0;
}