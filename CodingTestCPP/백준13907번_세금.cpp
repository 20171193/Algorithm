// 백준13907번 : 세금(https://www.acmicpc.net/problem/13907)
// 조건
// 1. 양방향 도로
// 2. 세금이 오르면 모든 도로가 한 번에 오름
// 3. 도시(N<=1,000), 도로(M<=30,000), 세금 인상 횟수(K<=30,000), 통행료(w<=1,000)
// 4. 0~K번째 세금이 올랐을 때의 통행료 출력 (출발도시 - 도착도시)
// 5. 최대 비용  
// 
// 풀이
// 1. 비용 기준 K번 다익스트라 -> 불가
//  : 미리 모든 경로 비용 구하기 (비용, 경로개수)
//  : +경로 개수 카운팅 
// 2. 경로 개수 * 세금
// 
// 시도
// 1. 실패(3%)
//  -> 양방향 간선 포맷안함..;
//
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <string>
using namespace std;
typedef long long ll;

constexpr int MAX_COST = 1000001;

int n, m, k, s, d, a, b, w;
int tax[30001];	// 1-based

struct Edge {
	int to;
	int cost;
	Edge(int to, ll cost) : to(to), cost(cost) {}
};

struct comparer {
	bool operator()(const pair<Edge, int>& a, const pair<Edge, int>& b) const {
		if (a.first.cost == b.first.cost)
			return a.second > b.second;
		else
			return a.first.cost > b.first.cost;
	}
};

vector<vector<Edge>> edges;

// pair<간선개수, 비용>
vector<pair<int, int>> dijkstra() {
	vector<pair<int, int>> ret;

	vector<vector<int>> costs(n + 1, vector<int>(n + 1, MAX_COST));

	// 간선, 간선 개수 
	priority_queue<pair<Edge, int>, vector<pair<Edge, int>>, comparer> pq;

	pq.push({ {s, 0}, 0 });
	costs[s][0] = 0;

	while (!pq.empty()) {
		int curNode = pq.top().first.to;
		int curCost = pq.top().first.cost;
		int curCount = pq.top().second;
		pq.pop();

		// 이미 갱신된 경로 
		if (costs[curNode][curCount] < curCost) continue;
		// 최대 간선개수
		if (curCount >= n - 1) continue;

		// 더 적은 간선에서 저렴한 비용이 있는지 확인
		bool flag = false;
		for (int i = 0; i < curCount; i++) {
			if (costs[curNode][i] <= curCost) {
				flag = true;
				break;
			}
		}
		if (flag) continue;

		for (Edge& nextEdge : edges[curNode]) {
			int nextNode = nextEdge.to;
			int nextCost = nextEdge.cost + curCost;

			if (costs[nextNode][curCount + 1] <= nextCost) continue;

			costs[nextNode][curCount + 1] = nextCost;
			pq.push({ {nextNode,  nextCost}, curCount + 1 });
		}
	}

	// 반환값 할당 (경로개수, 총 비용)
	for (int i = 0; i <= n; i++) {
		if (costs[d][i] != MAX_COST)
			ret.push_back({ i, costs[d][i] });
	}

	return ret;
}

vector<ll> solution() {
	// 0-based 변환 후 반환
	vector<ll> ret(k + 1);
	// 비용/경로 개수
	vector<pair<int, int>> costs = dijkstra();

	// 세금 추가 (1-based)
	// ret[0] = 세금없는 최초 비용 
	for (int i = 0; i <= k; i++) {
		ll mn = LLONG_MAX;
		for (const auto& cost : costs) {
			mn = min(mn, (ll)cost.first * tax[i] + cost.second);
		}
		ret[i] = mn;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	// input 1-based
	cin >> n >> m >> k >> s >> d;
	edges.assign(n + 1, {});
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> w;
		edges[a].push_back({ b,w });
		edges[b].push_back({ a,w });
	}

	// input 1-based
	for (int i = 1; i <= k; i++) {
		cin >> tax[i];
		tax[i] += tax[i - 1];
	}

	vector<ll> answer = solution();
	for (const ll& ans : answer)
		cout << ans << '\n';
	return 0;
}