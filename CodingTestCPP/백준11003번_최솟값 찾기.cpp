// 백준 11003번 : 최솟값 찾기
// 힙 방식 (Nlog(N))
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1000000001;
int n, l;
vector<int> answer;

struct comp
{
	bool operator()(const pair<int, int>& a, const pair<int, int>& b)
	{
		return a.first > b.first;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> l;
	priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;

	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		pq.push({ temp, i });
		while (i - pq.top().second >= l)
			pq.pop();

		answer.push_back(pq.top().first);
	}

	for (int i : answer)
		cout << i << ' ';
	return 0;
}