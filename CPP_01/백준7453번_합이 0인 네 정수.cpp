// 백준 7453번 : 합이 0인 네 정수
#include <iostream>
#include <unordered_map>
#include <math.h>
using namespace std;

int n, arr[4][4001];

struct customHash
{
	size_t operator()(int num) const
	{
		uint64_t unum = static_cast<uint64_t>(abs(num));
		return unum ^ (unum << 13);
	}
};

// 2 * n^2 = 32,000,000
int solve()
{
	unordered_map<int, int, customHash> abSums;
	// ab합
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			abSums[arr[0][i] + arr[1][j]]++;

	// cd합
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// -1 * cdSum
			int cdSum = -(arr[2][i] + arr[3][j]);
			if (abSums.find(cdSum) != abSums.end())
				count += abSums[cdSum];
		}
	}

	return count;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 4; j++)
			cin >> arr[j][i];

	cout << solve() << '\n';

	return 0;
}