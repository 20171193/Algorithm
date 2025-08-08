// ���� 2170�� : �� �߱�
#include <iostream>
#include <algorithm>
using namespace std;

int n;
pair<int, int> seg[1000001];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> seg[i].first >> seg[i].second;

	sort(seg, seg + n);

	int length = 0;
	pair<int, int> prev = seg[0];
	for (int i = 1; i < n; i++)
	{
		pair<int, int> cur = seg[i];
		// ��ħ
		if (cur.first <= prev.second)
		{
			// ����
			if (cur.second <= prev.second)
				continue;
			// �Ϻ� ��ħ
			prev.second = cur.second;
		}
		// �ٸ� ����
		else
		{
			length += prev.second - prev.first;
			prev = cur;
		}
	}
	length += prev.second - prev.first;

	cout << length << '\n';

	return 0;
}