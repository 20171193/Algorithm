// ���� 15663�� N�� M(9)

#include <iostream>
#include <algorithm>
using namespace std;

int n, m, arr[9], nums[9];
bool used[9];

// �ߺ����� �����ϴ� ����
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

	// �ߺ��� ������ ���ϱ� ����
	int prev = 0;

	for (int i = 0; i < n; i++)
	{
		// �ߺ��Ǿ��ų� ����� ��
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