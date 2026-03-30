// 백준 16938번 - 캠프 준비
#include <iostream>
#include <algorithm>
using namespace std;

// L <= 난이도의 합 <= R
// X <= (가장 어려운 문제 - 가장 쉬운 문제)

const int INF = 987654321;
int ret, n, l, r, x, arr[15];

int main()
{
	cin >> n >> l >> r >> x;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int i = 3; i < (1 << n); i++)
	{
		int cnt = 0, sum = 0, easy = INF, hard = -1;
		for (int j = 0; j < n; j++)
		{
			if (i & (1 << j))
			{
				easy = min(easy, arr[j]);
				hard = max(hard, arr[j]);
				sum += arr[j];
				cnt++;
			}
		}

		if (cnt < 2) continue;
		if (sum < l || sum > r || hard - easy < x) continue;

		ret++;
	}

	cout << ret << '\n';
	return 0;
}