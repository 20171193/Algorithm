// 백준 15663번 N과 M(9)

#include <iostream>
#include <algorithm>
using namespace std;

int n, m, arr[9], nums[9];
bool used[9];

// 중복없이 증가하는 순열
void Perm(int depth)
{
	if (depth == m)
	{
		for (int i = 0; i < m; i++)
		{
			cout << nums[i] << ' ';
		}
		cout << '\n';
		return;
	}

	// 중복된 수열을 피하기 위함
	int prev = 0;

	for (int i = 0; i < n; i++)
	{
		// 중복되었거나 사용한 수
		if (used[i] || arr[i] == prev) continue;

		nums[depth] = arr[i];
		prev = arr[i];
		used[i] = true;
		Perm(depth + 1);
		used[i] = false;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	sort(arr, arr + n);

	Perm(0);
	return 0;
}