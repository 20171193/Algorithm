// ���� 2568�� : ������ 2
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int n;
pair<int, int> edges[100001];

vector<int> solve()
{
	vector<int> result;

	sort(edges, edges + n);

	// b���� LIS (������ ����)
	vector<int> lis;
	// ������ �ε���
	vector<int> lisIdx(n);
	// ������ 
	vector<int> prev(n, -1);
	for (int i = 0; i < n; i++)
	{
		int to = edges[i].second;
		int pos = lower_bound(lis.begin(), lis.end(), to) - lis.begin();

		if (pos == lis.size())
			lis.push_back(to);
		else
			lis[pos] = to;

		lisIdx[i] = pos;

		// ���� ��� �Ҵ�
		for (int j = i - 1; j >= 0; j--)
		{
			if (lisIdx[j] == pos - 1 && edges[j].second < to)
			{
				prev[i] = j;
				break;
			}
		}
	}

	// ������ ������ �ε��� �Ҵ�
	int lastIdx = -1;
	for (int i = n - 1; i >= 0; i--)
	{
		if (lisIdx[i] == lis.size() - 1)
		{
			lastIdx = i;
			break;
		}
	}

	// ���ŵ� ������ ���� ���� ����� ������ �Ҵ�
	int curIdx = lastIdx;
	unordered_set<int> linked;
	while (curIdx != -1)
	{
		linked.insert(curIdx);
		curIdx = prev[curIdx];
	}

	for (int i = 0; i < n; i++)
	{
		if (linked.find(i) == linked.end())
			result.push_back(edges[i].first);
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> edges[i].first >> edges[i].second;

	vector<int> answer = solve();
	cout << answer.size() << '\n';
	for (int ans : answer)
		cout << ans << '\n';

	return 0;
}