// 백준27172번 : 수 나누기 게임
#include <iostream>
using namespace std;

const int MAX = 1000001;

int n, cards[100001], scores[MAX];
bool used[MAX];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input 
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> cards[i];
		used[cards[i]] = true;
	}

	// solve
	for (int cur = 1; cur < MAX; cur++)
	{
		if (!used[cur]) continue;

		for (int step = cur * 2; step < MAX; step += cur)
		{
			if (!used[step]) continue;

			scores[cur]++;
			scores[step]--;
		}
	}

	// output
	for (int i = 0; i < n; i++)
		cout << scores[cards[i]] << ' ';

	return 0;
}