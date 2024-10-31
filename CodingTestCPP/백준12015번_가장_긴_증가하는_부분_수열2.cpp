// 백준12015번 : 가장 긴 증가하는 부분 수열2
#include <iostream>
#include <vector>
using namespace std;

int n, arr[1000001], dp[1000001];

int BinarySearch(int l, int r, int num)
{
	int mid = 0;
	while (l <= r)
	{
		mid = (l + r) / 2;
		if (dp[mid] >= num)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return l;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	int cnt = 0;
	dp[0] = arr[0];
	// 길이를 고려했을 때 가장 최소 값으로 갱신
	for (int i = 1; i < n; i++)
	{
		// 큰 값이 나온 경우
		if (dp[cnt] < arr[i])
			dp[++cnt] = arr[i];
		// 기존 값 체크
		else
		{
			int index = BinarySearch(0, cnt, arr[i]);
			dp[index] = arr[i];
		}
	}

	cout << cnt + 1 << '\n';

	return 0;
}