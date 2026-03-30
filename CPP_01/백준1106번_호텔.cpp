// 백준 1106번 : 호텔
#include <iostream>
#include <algorithm>
using namespace std;

// 1 <= n <= 20
// 1 <= c <= 1000

// 배낭문제 풀이
const int INF_COST = 200001, INF_PEOPLE = 1101;
int n, c, costPerPeople[INF_PEOPLE];

pair<int, int> inputs[21];

int solve()
{
	int answer = INF_COST;
	fill(costPerPeople, costPerPeople + INF_PEOPLE, INF_COST);

	costPerPeople[0] = 0;
	for (int i = 0; i < n; i++)
	{
		int cost = inputs[i].first;
		int pep = inputs[i].second;

		for (int j = pep; j < INF_PEOPLE; j++)
		{
			costPerPeople[j] = min(costPerPeople[j], costPerPeople[j - pep] + cost);
			if (j >= c && costPerPeople[j] < answer)
				answer = costPerPeople[j];
		}
	}

	return answer;
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