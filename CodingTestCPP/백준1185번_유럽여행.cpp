// 백준 1185번 : 유럽여행(https://www.acmicpc.net/problem/1185)
// 조건
// 1. N개 나라(N <=10,000), P개의 길(P<=100,1000) 중 N-1개의 길만 남김
// 2. 최소 비용 트리 - MST
// 3. 각 노드마다 방문 비용(C<=1,000)이 있음 
//  - 총 비용 : 도로 비용 + 방문 비용
//  - 비용기반 union-find
// 4. 시작나라에서 시작 나라로 돌아와야 함.
//  - 시작나라는 '두 번' 방문해야 함.

// 시도
// 1. 비용 기반 MST 실패(조건오류)
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

struct Edge
{
	int _from, _to, _cost;
	Edge(int from, int to, int cost) :_from(from), _to(to), _cost(_cost) {}
	bool operator<(const Edge& other) const
	{
		return _cost > other._cost;
	}
	bool operator>(const Edge& other) const
	{
		return _cost < other._cost;
	}
};

struct UnionFindByCost
{
private:
	int _n;
	vector<int> _cost, _rank, _parent;

public:
	UnionFindByCost(int n)
	{
		_n = n;
		_cost.assign(_n, 0);
		_rank.assign(_n, 0);
		_parent.assign(_n, 0);
		iota(_parent.begin(), _parent.end(), 0);
	}

	// 경로 압축 + 비용 누적
	int Find(int a)
	{
		if (_parent[a] == a) return a;

		int pa = _parent[a];
		_parent[a] = Find(_parent[a]);
		_cost[a] += _cost[pa];	// 비용 누적
		return _parent[a];
	}

	void Union(const Edge& edge)
	{
		Union(edge._from, edge._to, edge._cost);
	}
	void Union(int a, int b, int cost)
	{
		int pa = Find(a);
		int pb = Find(b);

		if (pa == pb) return;

		// 새 경로 생성
		if (_rank[pa] < _rank[pb])
		{
			_parent[pa] = pb;
			// a-b를 cost로 연결
			// a-b = a-pa-pb-b
			// cost = _cost[a] + _cost[pa] - (_cost[b])
			_cost[pa] = _cost[b] - _cost[a] + cost;
		}
		else // _rank[pa] >= _rank[pb]
		{
			_parent[pb] = pa;

			// cost = _cost[b] + _cost[pb] - (_cost[a])
			_cost[pb] = _cost[a] - _cost[b] + cost;

			if (_rank[pa] == _rank[pb])
				_rank[pa]++;
		}
	}
};

int n, p, visitCosts[10001];
vector<Edge> edges;

int solution()
{
	UnionFindByCost ufc(n);

	sort(edges.begin(), edges.end(), less<Edge>());

	// 노드 비용 추가
	for (Edge& e : edges)
		e._cost += visitCosts[e._from] + visitCosts[e._to];

	// mst 비용 할당
	int mstCost = 0;
	for (const Edge& e : edges)
	{
		if (ufc.Find(e._from) != ufc.Find(e._to))
		{
			ufc.Union(e);
			mstCost += e._cost;
		}
	}

	// 최종적으로 가장 저렴한 노드+ (시작 노드 두 번 방문)
	mstCost += *min_element(visitCosts, visitCosts + n);
	return mstCost;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// 1-based input
	cin >> n >> p;
	for (int i = 1; i <= n; i++)
		cin >> visitCosts[i];
	for (int i = 0; i < p; i++)
	{
		int from, to, cost;
		cin >> from >> to >> cost;
		edges.push_back({ from, to, cost });
	}

	cout << solution() << '\n';
	return 0;
}
