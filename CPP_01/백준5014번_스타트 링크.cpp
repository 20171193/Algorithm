#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const string FAIL = "use the stairs";
const int MAX_FLOOR = 1000000;

// f : 총 층 개수
// s : 현재 층
// g : 스타트 링크 층
// u : 위로 한 번 이동하는 층 수
// d : 아래로 한 번 이동하는 층 수
int f, s, g, dir[2];

int visited[MAX_FLOOR + 1];

void bfs()
{
	queue<int> q;
	q.push(s);
	visited[s] = 1;

	while (q.size())
	{
		int cur = q.front();
		q.pop();

		if (visited[g] && visited[cur] > visited[g])
			continue;

		for (int i = 0; i < 2; i++)
		{
			int next = i == 0 ? cur + dir[i] : cur - dir[i];
			if (next < 1 || next > f)
				continue;
			if (visited[next])
				continue;

			visited[next] = visited[cur] + 1;
			q.push(next);
		}
	}
}

int main()
{
	cin >> f >> s >> g >> dir[0] >> dir[1];

	bfs();

	if (visited[g])
		cout << visited[g] - 1 << '\n';
	else
		cout << FAIL << '\n';

	return 0;
}