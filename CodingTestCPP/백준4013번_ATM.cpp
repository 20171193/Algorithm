// 백준 4013번 : ATM(https://www.acmicpc.net/problem/4013)
// 조건
// 1. 간선(M<=500,000) : 단 방향
// 2. 노드(N<=500,000) : ATM / ATM+체인점
// 3. 중복 방문 가능
// 4. 가장 많은 현금을 인출해 레스토랑에 도착했을 때, 현금의 액수
// 5. atm(<=4,000) 
// 
// 풀이
// 1. 상태 탐색?
//   : 상태마다 atm 방문 정보가 있어야 함. (500,000 : 비트 마스킹 불가)
// 2. 사이클 자체를 하나의 노드로 만들기. (SCC)
//  2-1. dfs로 scc구하기
//  2-2. (bfs+방문체크dp)로 scc 간선 탐색 최대 비용 출력
// 
// 시도
// 1. dfs + bfs(+dp) 성공      / 173424kb, 376ms
// 2. dfs + 위상정렬(+dp) 성공 / 105108kb, 312ms (.-70000kb, .-60ms)
//                             / 큐 중복 삽입, 방문체크 배열 절약	
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

vector<vector<int>> edges;
int n, m, s, p, atm[500001];
bool isRestaurant[500001];

// dfs(scc) 전역
// 방문 순서, 최소 방문 순서, scc루트
int dfs_num[500001], low_link[500001], scc_root[500001], scc_cost[500001];
// 레스토랑이 속한 SCC
bool isRestaurantSCC[500001];
int dfsCount = 0, sccCount = 0;
// 노드 스태킹
bool onStack[500001];
// 스택 대용 vector
vector<int> st;

// bfs 전역 (방문체크 scc 루트)
int visited[500001];

// 기존 그래프 탐색, scc 할당
void dfs(int node) {
	dfs_num[node] = low_link[node] = ++dfsCount;
	st.push_back(node);
	onStack[node] = true;

	for (int to : edges[node]) {
		// 방문하지 않은 노드일 경우
		if (dfs_num[to] == 0) {
			dfs(to);
			// 해당 노드 dfs후 low_link처리
			low_link[node] = min(low_link[node], low_link[to]);
		}
		// 방문했으며, 스택에 존재
		else if (onStack[to]) {
			low_link[node] = min(low_link[node], low_link[to]);
		}
	}
	// 연결된 노드 탐색이후에도 현재 노드가 루트노드일 경우
	if (low_link[node] == dfs_num[node]) {
		++sccCount;
		while (true) {
			int cur = st.back();
			st.pop_back();
			onStack[cur] = false;
			scc_root[cur] = sccCount;
			// 사이클 비용 할당
			scc_cost[sccCount] += atm[cur];
			if (isRestaurant[cur])
				isRestaurantSCC[sccCount] = true;
			if (cur == node) break;
		}
	}
}
// 시도 2. 위상정렬
//  : scc 그래프는 단방향 -> 위상정렬 가능
//  : 노드 중복 삽입없이 sccCount만큼 삽입 (메모리, 시간 절약)
int DP() {
	int maxCost = -1;

	vector<vector<int>> sccEdges(sccCount + 1);
	vector<int> indegree(sccCount + 1, 0);

	for (int f = 1; f <= n; f++) {
		int fr = scc_root[f];
		for (int t : edges[f]) {
			int tr = scc_root[t];
			if (fr == tr) continue;

			sccEdges[fr].push_back(tr);
			indegree[tr]++;
		}
	}

	queue<int> q;
	for (int i = 1; i <= sccCount; i++)
		if (indegree[i] == 0)
			q.push(i);


	vector<int> dp(sccCount + 1, -1);
	int startRoot = scc_root[s];
	dp[startRoot] = scc_cost[startRoot];

	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (int next : sccEdges[cur]) {
			if (dp[cur] != -1)
				dp[next] = max(dp[next], dp[cur] + scc_cost[next]);
			if (--indegree[next] == 0)
				q.push(next);
		}
	}

	for (int i = 1; i <= sccCount; i++)
		if (isRestaurantSCC[i])
			maxCost = max(maxCost, dp[i]);

	return maxCost;
}

// 시도 1. BFS
// scc 그래프 탐색, 최대 비용 반환(DP) 
int bfs() {
	int maxCost = -1;

	// scc간 간선 생성
	vector<unordered_set<int>> sccEdges(sccCount + 1);
	for (int from = 1; from <= n; from++) {
		int fromRoot = scc_root[from];
		for (int to : edges[from]) {
			int toRoot = scc_root[to];
			if (fromRoot == toRoot) continue;

			sccEdges[fromRoot].insert(toRoot);
		}
	}

	queue<int> q;
	int startRoot = scc_root[s];
	q.push(startRoot);
	visited[startRoot] = scc_cost[startRoot];

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		// 레스토랑이 속한 경우 DP
		if (isRestaurantSCC[cur])
			maxCost = max(maxCost, visited[cur]);

		for (int next : sccEdges[cur]) {
			int nextCost = visited[cur] + scc_cost[next];
			if (visited[next] >= nextCost) continue;

			visited[next] = nextCost;
			q.push(next);
		}
	}
	return maxCost;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	edges.assign(n + 1, {});

	int from, to;
	for (int i = 0; i < m; i++) {
		cin >> from >> to;
		edges[from].push_back(to);
	}

	for (int i = 1; i <= n; i++)
		cin >> atm[i];

	cin >> s >> p;
	int rtr;
	for (int i = 0; i < p; i++) {
		cin >> rtr;
		isRestaurant[rtr] = true;
	}

	// scc 할당
	for (int i = 1; i <= n; i++) {
		if (dfs_num[i] == 0)
			dfs(i);
	}
	cout << DP() << '\n';
	return 0;
}