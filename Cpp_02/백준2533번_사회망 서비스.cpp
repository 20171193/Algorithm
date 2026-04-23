// 백준 2533번 : 사회망 서비스
// 조건
// 1. 사회망 : 정점(사람), 간선(친구 관계)
// 2. 얼리어답터(ea) : 현재 노드가 ea가 아니고, 연결된 다른 모든 노드가 ea일 때 조건을 만족
//                   : 모든 노드가 조건을 만족하기위한 ea의 최소 개수
// 3. 사이클은 없음
// 풀이
// 1. dp[n][2] : 상태에 따른 ea 총 개수 
//      [i][0] : i노드가 ea가 아닌경우
//      [i][1] : i노드가 ea인 경우
// 2. dfs : 임의 노드(루트)부터 리프까지 깊이 탐색
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> graph, dp;

void dfs(int cur, int parent) {
	dp[cur][0] = 0;
	dp[cur][1] = 1;
	for (int next : graph[cur]) {
		if (next == parent) continue;
		dfs(next, cur);

		// 내가 ea가 아니라면 자식은 무조건 ea
		dp[cur][0] += dp[next][1];
		// 내가 ea라면 자식은 자유
		dp[cur][1] += min(dp[next][0], dp[next][1]);
	}
}

int solution() {
	dp.assign(n + 1, vector<int>(2));
	// 루트를 1로 설정
	dfs(1, -1);
	return min(dp[1][0], dp[1][1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	graph.assign(n + 1, {});
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	cout << solution() << '\n';
	return 0;
}