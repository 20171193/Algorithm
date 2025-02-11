// 백준 2961번 도영이가 만든 맛있는 음식
#include <iostream>
#include <math.h>
using namespace std;

typedef long long ll;

int n;
ll ret = -1;
pair<int, int> igds[11];

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> igds[i].first >> igds[i].second;

	for (int i = 1; i < (1 << n); i++)
	{
		ll a = 1, b = 0;
		for (int j = 0; j < n; j++)
		{
			if (i & (1 << j))
			{
				a *= igds[j].first;
				b += igds[j].second;
			}
		}
		ret = ret == -1 ? abs(a - b) : min(ret, abs(a - b));
	}

	cout << ret << '\n';

	return 0;
}