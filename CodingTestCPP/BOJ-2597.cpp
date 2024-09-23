// ���� 2579�� ��� ������

// �� ���� �� ��� �Ǵ� �� ��ܾ� ���� �� ����.
// ���ӵ� �� ���� ����� ��� ��Ƽ��� �� ��.
#include <iostream>
#include <algorithm>
using namespace std;

int n, a[301], dp[301];

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	dp[0] = a[0];
	dp[1] = max(a[0] + a[1], a[1]);

	for (int i = 2; i < n; i++)
	{
		dp[i] = max(dp[i - 2], dp[i - 2] + a[i - 1] + a[i]);
	}

	cout << dp[n - 1] << '\n';
	return 0;
}