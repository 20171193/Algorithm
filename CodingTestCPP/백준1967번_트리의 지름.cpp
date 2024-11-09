// 백준1967번 트리의 지름
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <math.h>
#include <chrono>
using namespace std;

int n, ret;
bool dfsVisited[10001];
int bfsVisited[10001];
// BFS 탐색 
void bfs(int start, vector<vector<pair<int, int>>>& vec)
{
	// 방문배열 초기화
	memset(bfsVisited, -1, sizeof(int) * (vec.size()));

	queue<int> q;
	bfsVisited[start] = 0;
	q.push(start);

	while (q.size())
	{
		int cur = q.front();
		q.pop();

		for (int i = 0; i < vec[cur].size(); i++)
		{
			int next = vec[cur][i].first;
			int value = vec[cur][i].second;

			if (bfsVisited[next] != -1)
				continue;

			bfsVisited[next] = bfsVisited[cur] + value;

			// 다음 노드가 리프노드인 경우는 거리 갱신 후 추가하지 않음.
			if (vec[next].size() == 1)
			{
				ret = max(bfsVisited[next], ret);
				continue;
			}
			else
				q.push(next);
		}
	}
}

// DFS 탐색
void dfs(int cur, int dist, vector<vector<pair<int, int>>>& vec)
{
	dfsVisited[cur] = true;

	for (int i = 0; i < vec[cur].size(); i++)
	{
		int next = vec[cur][i].first;
		int value = vec[cur][i].second;
		if (dfsVisited[next])
			continue;

		if (vec[next].size() > 1)
			dfs(next, dist + value, vec);
		else
			ret = max(dist + value, ret);
	}
}

int main()
{
	cin >> n;
	vector<vector<pair<int, int>>> vec(n + 1);

	for (int i = 0; i < n - 1; i++)
	{
		int s, e, v;
		cin >> s >> e >> v;
		vec[s].push_back({ e,v });
		vec[e].push_back({ s,v });
	}

	auto start = chrono::high_resolution_clock::now();
	for (int i = 1; i <= n; i++)
	{
		//   시간 효율 : bfs < dfs (현 깊이의 모든 노드확인 <-> 리프노드까지 보지 않음, 방문노드 건너뜀)
		// 메모리 효율 : bfs > dfs (함수호출스택)
		if (vec[i].size() == 1)
			//bfs(i, vec);		
		{
			dfs(i, 0, vec);
			memset(dfsVisited, false, sizeof(bool) * vec.size());
		}
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

	auto start2 = chrono::high_resolution_clock::now();
	for (int i = 1; i <= n; i++)
	{
		//   시간 효율 : bfs < dfs (현 깊이의 모든 노드확인 <-> 리프노드까지 보지 않음, 방문노드 건너뜀)
		// 메모리 효율 : bfs > dfs (함수호출스택)
		if (vec[i].size() == 1)
			bfs(i, vec);
	}
	auto end2 = chrono::high_resolution_clock::now();
	auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);

	cout << "DFS : " << duration.count() << '\n';
	cout << "BFS : " << duration2.count() << '\n';

	return 0;
}