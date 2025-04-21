// 백준 1806번 : 부분합
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 100001;
int n, s, arr[100001];

int main()
{
	cin >> n >> s;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	int l = 0, r = -1, sum = 0, minLen = INF;
	while (r < n)
	{
		if (sum >= s)
		{
			minLen = min(minLen, r - l + 1);
			sum -= arr[l++];
		}
		else
			sum += arr[++r];
	}

	if (minLen == INF)
		cout << 0 << '\n';
	else
		cout << minLen << '\n';

	return 0;
}