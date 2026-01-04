// 백준 20188번 : 등산 마니아(https://www.acmicpc.net/problem/20188)
// 조건
// 1. 노드n(<=300,000), 간선n-1, 트리 형태로 연결되어있음.
// 2. 노드는 1번 부터 N번까지, 1번은 항상 루트
// 3. 한 노드에서 다른 노드로 갈 때 항상 루트를 거침
//  3-1. 해당 경로에서 중복 사용된 간선은 세지 않음.
//  3-2. i~n까지 모든 다양성을 출력
// 
// 풀이
// 1. i~j까지의 다양성 (시간초과)
//  1-1. i와 j가 동시에 속한 서브트리의 루트(sr) 찾기 
//  1-2. (sr~r) + (i~sr) + (j~sr) 
// 2. 간선 기여도 풀이
//  => 해당 간선을 끊었을 때, 각 서브트리에 기여하는 정도
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

typedef long long ll;

int n, root[300001], depth[300001], treeSize[300001];
pair<int, int> input[300000];
vector<vector<int>> edges;

int dfs(int cur, int parent) {
	// 루트를 포함하는 서브 트리의 크기
	int size = 1;
	for (int next : edges[cur]) {
		if (next == parent) continue;
		size += dfs(next, cur);
	}
	treeSize[cur] = size;
	return size;
}

ll solution() {
	ll answer = 0;

	// 그래프 포맷
	edges.assign(n + 1, {});
	for (int i = 0; i < n - 1; i++) {
		edges[input[i].first].push_back(input[i].second);
		edges[input[i].second].push_back(input[i].first);
	}

	memset(depth, -1, sizeof(int) * (n + 1));
	// bfs로 root, depth 할당
	queue<int> q;
	q.push(1);
	root[1] = depth[1] = 0;
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (int next : edges[cur]) {
			if (depth[next] != -1) continue;

			root[next] = cur;
			depth[next] = depth[cur] + 1;
			q.push(next);
		}
	}
	// *기존 풀이 (공통 루트 찾기 + 모든 간선 계산 n^3)
	// n^2:60,000,000,000만 해도 불가, find root까지 최악 n^3
	//  for (int i = 1; i <= n - 1; i++) {
	//		for (int j = i + 1; j <= n; j++) {
	//			int sr = findroot(i, j);
	//			answer += depth[i] + depth[j] - depth[sr];
	//		}
	//	}
	// *변경 (간선 별 기여도 할당 n)
	//   1. 해당 간선을 끊었을 때, 두 서브 트리의 곱
	//   2. + 메인 루트를 포함하지 않는 서브 트리의 루트에서 메인 루트까지의 거리  

	// dfs로 각 노드를 루트로 하는 서브트리의 개수 할당
	dfs(1, 0);

	// 전체에서 2개 뽑는 조합
	ll totalComb = 1LL * n * (n - 1) / 2;
	for (int i = 2; i <= n; i++) {
		// left : 서브트리
		ll leftSize = treeSize[i];
		// right : 메인 루트를 포함하는 트리
		ll rightSize = n - leftSize;

		// 현재 간선 안쓰고 우측 트리에서만 뽑는경우
		ll rightComb = rightSize * (rightSize - 1) / 2;
		answer += totalComb - rightComb;
	}

	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 0; i < n - 1; i++)
		cin >> input[i].first >> input[i].second;

	cout << solution() << '\n';
	return 0;
}

