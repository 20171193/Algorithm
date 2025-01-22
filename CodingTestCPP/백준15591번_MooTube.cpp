// น้มุ 15591น๘ MooTube
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

typedef long long ll;

struct Edge
{
public:
	int _end;
	int _value;

	Edge(int end, int value) : _end(end), _value(value) {}
};

vector<Edge> edges[5001];
vector<int> ans;
int N, Q;
bool visited[5001];

int solution(int k, int v)
{
	int cnt = 0;

	queue<int> q;
	q.push(v);
	visited[v] = true;

	while (q.size())
	{
		int cur = q.front();
		q.pop();

		for (int i = 0; i < edges[cur].size(); i++)
		{
			int next = edges[cur][i]._end;
			int value = edges[cur][i]._value;

			if (visited[next]) continue;
			if (value < k) continue;

			visited[next] = true;
			q.push(next);
			cnt++;
		}
	}

	memset(visited, false, N + 1);
	return cnt;
}

int main()
{
	// input 
	cin >> N >> Q;
	for (int i = 0; i < N - 1 + Q; i++)
	{
		if (i < N - 1)
		{
			int p, q, r;
			cin >> p >> q >> r;
			edges[p].push_back(Edge(q, r));
			edges[q].push_back(Edge(p, r));
		}
		else
		{
			int k, v;
			cin >> k >> v;
			ans.push_back(solution(k, v));
		}
	}

	// output
	for (int answer : ans)
		cout << answer << '\n';

	return 0;
}