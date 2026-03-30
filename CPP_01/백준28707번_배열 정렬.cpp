//백준 28707번 : 배열 정렬
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int MAX_LENGHT = 8, MAX_NUMBER = 10, FIRST_ALPHA = 65;
const int LEFT_INDEX = 0, RIGHT_INDEX = 1, COST_INDEX = 2;

int n, m, arr[MAX_LENGHT + 1], options[11][3];

struct comp
{
	bool operator()(const pair<string, int>& a, const pair<string, int>& b)
	{
		return a.second > b.second;
	}
};

// 알파벳으로 변환
string ConvertIntArray(const int* origin, int length)
{
	string result;
	for (int i = 0; i < length; i++)
		result += (char)(origin[i] + FIRST_ALPHA);
	return result;
}

int solve()
{
	int answer = -1;

	// 기존 배열 포맷
	string origin = ConvertIntArray(arr, n);
	// 목표 배열 포맷(오름차)
	sort(arr, arr + n);
	string target = ConvertIntArray(arr, n);

	unordered_map<string, int> visited;
	priority_queue<pair<string, int>, vector<pair<string, int>>, comp> pq;
	pq.push({ origin, 0 });
	visited.insert({ origin, 0 });

	while (!pq.empty())
	{
		string curState = pq.top().first;
		int curCost = pq.top().second;
		pq.pop();

		for (int i = 0; i < m; i++)
		{
			int left = options[i][LEFT_INDEX] - 1;
			int right = options[i][RIGHT_INDEX] - 1;
			int cost = options[i][COST_INDEX];

			string nextState = curState;
			swap(nextState[left], nextState[right]);
			int nextCost = curCost + cost;

			if (visited.find(nextState) == visited.end()
				|| visited[nextState] > nextCost)
			{
				visited[nextState] = nextCost;
				pq.push({ nextState, nextCost });
			}
		}
	}

	if (visited.find(target) == visited.end())
		return -1;
	else
		return visited[target];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	cin >> m;
	for (int i = 0; i < m; i++)
		cin >> options[i][LEFT_INDEX]
		>> options[i][RIGHT_INDEX]
		>> options[i][COST_INDEX];

	cout << solve() << '\n';

	return 0;
}