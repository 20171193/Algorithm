// 백준 1106번 : 호텔
#include <iostream>
#include <algorithm>
using namespace std;

// 1 <= n <= 20
// 1 <= c <= 1000

const int LIMIT_COST = 2001; // 제한선 이상 비용

int n, c, costPerPeople[1001];
pair<int, int> inputs[21];

bool cmp(const pair<int, int>& a, const pair<int, int>& b)
{
	return a.first > b.first;
}

int FindCost(int targetPeople)
{
	if (targetPeople <= 0)
		return 0;

	for (int pep = targetPeople; pep >= 0; pep--)
	{
		if (costPerPeople[pep] != LIMIT_COST)
			return costPerPeople[pep] + FindCost(targetPeople - pep);
	}
}

int solve()
{
	// 비용 기준 내림차 정렬
	sort(inputs, inputs + n, cmp);
	fill(costPerPeople, costPerPeople + c + 1, LIMIT_COST);

	// 최적의 비용으로 포맷
	for (int i = 0; i < n; i++)
	{
		int cost = inputs[i].first;
		int pep = inputs[i].second;

		int curCost = 0, curPep = 0;
		bool checkFlag = false;
		for (int j = pep; j <= c; j++)
		{
			if (j % pep == 0)
			{
				checkFlag = true;
				curCost += cost;
				curPep += pep;
			}

			if (costPerPeople[j] <= curCost)
				break;
			else if (checkFlag)
			{
				costPerPeople[j] = curCost;
				checkFlag = false;
			}
		}
	}

	for (int i = 1; i <= c; i++)
		cout << i << " : " << costPerPeople[i] << '\n';

	// To-do 배낭 문제

	return FindCost(c);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> c >> n;
	for (int i = 0; i < n; i++)
		cin >> inputs[i].first >> inputs[i].second;

	cout << solve() << '\n';

	return 0;
}