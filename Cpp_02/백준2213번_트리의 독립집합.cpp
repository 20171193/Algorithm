// 백준 2213번 : 트리의 독립집합
// 조건
// 1. 독립 집합 : 그래프 정점의 부분 집합 s에 속한 모든 정점쌍이 서로 인접하지 않은 집합
// 2. 독립 집합의 크기 : 독립 집합에 속한 정점의 가중치의 합
// 3. 사이클이 없는 그래프(트리)에서의 최대 독립 집합을 구하라
// 풀이
//  1. dp[n][2] : n을 미포함(0)/n을 포함(1)
//  2. dfs : 트리 깊이 탐색, 역추적 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int n, weights[10001];
vector<vector<int>> graph, dp;

void dfs(int cur, int parent) {
	dp[cur][0] = 0;
	dp[cur][1] = weights[cur];
	for (int next : graph[cur]) {
		if (next == parent) continue;
		dfs(next, cur);

		dp[cur][0] += max(dp[next][1], dp[next][0]);
		dp[cur][1] += dp[next][0];
	}
}
void backtrack(int cur, int parent, int prevChoose, vector<int>& path) {
	int curChoose = 0;
	// 부모를 포함한 경우
	if (prevChoose)
		curChoose = 0;
	// 포함하지 않은 경우
	else {
		if (dp[cur][0] > dp[cur][1])
			curChoose = 0;
		else {
			curChoose = 1;
			path.push_back(cur);
		}
	}

	for (int next : graph[cur]) {
		if (next == parent) continue;
		backtrack(next, cur, curChoose, path);
	}
}

vector<int> solution() {
	dp.assign(n + 1, vector<int>(2));
	dfs(1, -1);

	vector<int> result;
	// 역추적
	backtrack(1, -1, 0, result);

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> weights[i];

	graph.assign(n + 1, {});
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> answer = solution();

	// 출력 포맷
	int totalWeight = 0;
	string str;
	sort(answer.begin(), answer.end());
	for (int v : answer) {
		str += to_string(v) + ' ';
		totalWeight += weights[v];
	}

	cout << totalWeight << '\n';
	cout << str << '\n';

	return 0;
}