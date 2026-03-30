// 백준 1043번 : 거짓말
// 같은 파티에 속하는 경우를 제외
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int solution(int n, int m, const vector<vector<int>> partyInPeople, const vector<int> pepNum)
{
	int result = 0;

	vector<vector<int>> peopleToParty(n + 1, vector<int>());
	for (int i = 0; i < partyInPeople.size(); i++)
		for (int p : partyInPeople[i])
			peopleToParty[p].push_back(i);

	vector<bool> knowPeople(n + 1, false), impossibleParty(m, false);
	queue<int> q;
	for (int cur : pepNum)
	{
		if (knowPeople[cur]) continue;

		knowPeople[cur] = true;
		q.push(cur);

		while (!q.empty())
		{
			cur = q.front();
			q.pop();

			for (int party : peopleToParty[cur])
			{
				// 방문 불가한 파티 처리
				if (impossibleParty[party]) continue;
				impossibleParty[party] = true;

				// 해당 파티에 속한 사람 추가(큐) 
				for (int person : partyInPeople[party])
				{
					if (knowPeople[person]) continue;
					knowPeople[person] = true;
					q.push(person);
				}
			}
		}
	}

	for (bool impossible : impossibleParty)
	{
		if (!impossible)
			result++;
	}

	return result;
}


int main()
{
	int n = 0, m = 0;
	cin >> n >> m;

	int num = 0;
	cin >> num;
	vector<int> pepNum(num);	// 진실을 아는 사람들
	for (int i = 0; i < num; i++)
		cin >> pepNum[i];

	vector<vector<int>> partyInPeople;	// 파티에 속한 사람들
	for (int i = 0; i < m; i++)
	{
		cin >> num;
		vector<int> pip(num);
		for (int j = 0; j < num; j++)
			cin >> pip[j];
		partyInPeople.push_back(pip);
	}

	cout << solution(n, m, partyInPeople, pepNum) << '\n';

	return 0;
}