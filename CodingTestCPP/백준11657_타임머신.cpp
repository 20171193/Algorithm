// 백준 11657번 타임머신

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <memory.h>
#include <limits>
using namespace std;

// 벨만포드 알고리즘 
// - 한 정점에서 다른 모든 정점에 이르는 최단 경로 One to All
// - 음수 가중치의 간선이 존재
// - 음수 사이클일 경우 -1 출력
// - O(N*M), 3,000,000

typedef long long ll;
int n, m, a, b, c;
map<pair<int, int>, int> graph;
const ll MaxDist = numeric_limits<ll>::max();

// 탐색과 함께 사이클 여부판단
bool HasCycle(int start, vector<ll>& dists)
{
	// start 노드부터의 거리를 최대 거리로 초기화
	dists[start] = 0;

	// 최초 탐색 (거리 갱신)
	for (int i = 1; i < n; i++) {
		for (auto iter = graph.begin(); iter != graph.end(); iter++)
		{
			auto& edge = *iter;
			int s = edge.first.first;	// 시작 노드
			int e = edge.first.second;	// 끝 노드
			int v = edge.second;		// 간선 가중치

			if (dists[s] == MaxDist) continue;
			dists[e] = min(dists[e], dists[s] + v);
		}
	}

	// 음수 사이클 확인
	for (auto iter = graph.begin(); iter != graph.end(); iter++)
	{
		auto& edge = *iter;
		int s = edge.first.first;	// 시작 노드
		int e = edge.first.second;	// 끝 노드
		int v = edge.second;		// 간선 가중치

		if (dists[s] == MaxDist) continue;
		// 최초 탐색 거리보다 최단거리를 찾은 경우 (음수 사이클)
		if (dists[e] > dists[s] + v)
			return true;
	}
	return false;
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		if (graph.find({ a,b }) == graph.end())
			graph[{a, b}] = c;
		else
			graph[{a, b}] = min(graph[{a, b}], c);
	}

	vector<ll> dists(n + 1, MaxDist);
	bool hasCycle = HasCycle(1, dists);

	if (hasCycle)
		cout << -1 << '\n';
	else
	{
		for (int i = 2; i <= n; i++)
		{
			if (dists[i] == MaxDist)
				cout << -1 << '\n';
			else
				cout << dists[i] << '\n';
		}
	}

	return 0;
}