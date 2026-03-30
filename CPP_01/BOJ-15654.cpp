// น้มุ 15654 - Nฐ๚ M(5) (s3) 
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m, a[9], cur[9];
bool used[9];

void go(int cnt)
{
	if (cnt == m)
	{
		for (int i = 0; i < m; i++)
		{
			cout << cur[i] << ' ';
		}
		cout << '\n';
		return;
	}

	for (int i = 0; i < n; i++)
	{
		if (used[i]) continue;

		used[i] = true;
		cur[cnt] = a[i];
		go(cnt + 1);
		used[i] = false;
	}
}



int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	sort(a, a + n);
	go(0);

	return 0;
}