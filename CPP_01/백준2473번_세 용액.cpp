// 백준 2473번 : 세 용액
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll INF = 3000000001;
ll mn;
int n, arr[5001], answer[3];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	sort(arr, arr + n);

	// solve
	mn = INF;
	for (int fst = 0; fst < n - 2; fst++)
	{
		// fst = i
		int sec = fst + 1, thd = n - 1;
		while (sec < thd)
		{
			ll sum = (ll)arr[fst] + arr[sec] + arr[thd];
			if (abs(sum) < mn)
			{
				mn = abs(sum);
				answer[0] = arr[fst];
				answer[1] = arr[sec];
				answer[2] = arr[thd];
			}

			if (sum == 0)
				break;
			else if (sum > 0)
				thd--;
			else
				sec++;
		}
	}

	// output
	for (int i : answer)
		cout << i << ' ';

	return 0;
}