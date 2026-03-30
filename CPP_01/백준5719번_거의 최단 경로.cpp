// 백준 5719번 : 거의 최단 경로 (https://www.acmicpc.net/problem/5719)
// 
// 조건
// 1. 거의 최단 경로
//  : 최단 경로에 포함되지 않는 도로로만 이루어진 경로 중 가장 짧은 것
// 2. 거의 최단 경로의 길이를 출력
//
// 풀이
// 1. 최단 경로 찾기
//  1-1. 다익스트라
//  1-2. 경로 추적 후 제거
// 2. 두번째 다익스트라 비용 출력
//  2-1. 첫번째 다익스트라 비용과 같을 경우 1-1~2 반복 
//  2-2. 다를 경우 출력
// 
// 시도
// 1. 실패(8%) : 최적 경로가 여러 개 존재할 수 있음
//  -> 다익스트라 내 조건추가
//   : if(nextCost < dists[nextNode]) => if(nextCost <= dists[nextNode])
//   : 역추적으로 제거 할 경로 추가
// 2. 실패(25%) : 메모리 초과
//  -> 다익스트라 반복 제거 (단 두 번으로 종료)
//  -> 도로 활성화 여부 체크 용 2차원 배열 제거 구조체 내부에서 관리
//     -> 시간 복잡도는 도로 개수(m)에 비례해서 증가
//  -> 역추적 BFS 노드 방문 체크
//  -> 성공


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 장소개수(N<=500) * 도로길이(P<=1000)
constexpr int INF = 500001;

struct Edge {
	int cost, to;
	bool isEnable;
};

// 다익스트라 + 경로 제거
int dijkstra(int n, int start, int end, vector<vector<int>>& path, vector<vector<Edge>>& roads)
{
	vector<int> dists(n, INF);
	path.assign(n, {});

	// 비용 min-heap
	// pair<cost, node>
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, start });
	dists[start] = 0;

	while (!pq.empty())
	{
		int curCost = pq.top().first;
		int curNode = pq.top().second;
		pq.pop();

		if (dists[end] < curCost) continue;

		for (auto& road : roads[curNode])
		{
			// 도로 활성화 여부 확인
			if (!road.isEnable)
				continue;

			int nextCost = road.cost + curCost;
			int nextNode = road.to;

			// 경로 추가
			if (nextCost == dists[nextNode])
			{
				path[nextNode].push_back(curNode);
				continue;
			}

			// 경로 갱신
			if (nextCost < dists[nextNode])
			{
				path[nextNode] = { curNode };
				pq.push({ nextCost, nextNode });
				dists[nextNode] = nextCost;
			}
		}
	}

	if (dists[end] == INF)
		return -1;

	// BFS : 경로 역추적 + 도로 비활성화
	//DisableEdge(end, path, roads);
	queue<int> q;
	vector<bool> visited(n);
	q.push(end);
	visited[end] = true;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int prev : path[cur])
		{
			// 메모리 개선 (시간 복잡도는 증가)
			for (auto& road : roads[prev])
			{
				if (road.to == cur)
				{
					road.isEnable = false;
					break;
				}
			}

			if (!visited[prev])
			{
				visited[prev] = true;
				q.push(prev);
			}
		}
	}

	return dists[end];
}

int solution(int n, int m, int s, int d, vector<vector<Edge>>& roads)
{
	vector<vector<int>> path;

	// 첫 번째 최소 비용 탐색
	int fstCost = dijkstra(n, s, d, path, roads);

	// 두 번째 최소 비용 탐색
	int scdCost = dijkstra(n, s, d, path, roads);
	return scdCost;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, s, d, u, v, p;
	while (true)
	{
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;
		cin >> s >> d;

		vector<vector<Edge>> roads(n);
		for (int i = 0; i < m; i++)
		{
			cin >> u >> v >> p;
			roads[u].push_back({ p, v, true });
		}

		cout << solution(n, m, s, d, roads) << '\n';
	}

	return 0;
}