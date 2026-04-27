// 백준 14428번 : 수열과 쿼리 16
// 조건
// 1. 쿼리
//  1-1. 1 i v : A[i]를 v로 변경 (1<=i<=N, 1<=v<=10^9)
//  1-2. 2 i j : A[i]~A[j]에서 크기가 가장 작은 값의 인덱스를 출력
//               여러 개인 경우 가장 작은 인덱스 출력
// 2. 1-2번 쿼리에 대한 정답을 하나씩 출력
// 풀이
// 1. 세그먼트 트리
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
constexpr int INF_RANGE = 100001;
constexpr ll INF_VALUE = 1000000001;

int n, m;
pair<ll, int> arr[100001];	// <value, index>
tuple<int, int, ll> querys[100001];

struct SegmentTree {
	int _n;
	vector<pair<ll, int>> tree;
public:
	SegmentTree() {
		_n = n;
		tree.assign(_n * 4, { 0,0 });
		makeTree(1, 1, n);
	}

private:
	pair<ll, int> makeTree(int node, int l, int r) {
		if (l == r) return tree[node] = arr[l];

		int mid = (l + r) >> 1;
		auto left = makeTree(node * 2, l, mid);
		auto right = makeTree(node * 2 + 1, mid + 1, r);
		auto result = min(left, right);
		return tree[node] = result;
	}

public:
	// 1-1 : 값 갱신 쿼리(1 i v)
	pair<ll, int> updateTree(int node, int l, int r, const int idx, const ll value) {
		if (l == r && idx == l) return tree[node] = { value, idx };

		int mid = (l + r) >> 1;
		if (idx <= mid) updateTree(node * 2, l, mid, idx, value);
		else updateTree(node * 2 + 1, mid + 1, r, idx, value);

		return tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}

	// 1-2 : 최솟값 인덱스 쿼리(2 i j)
	pair<ll, int> getMin(int node, int l, int r, const int ql, const int qr) {
		if (ql > r || qr < l) return { INF_VALUE, INF_RANGE };	// 범위 예외
		if (ql <= l && r <= qr) return tree[node];

		int mid = (l + r) >> 1;
		auto left = getMin(node * 2, l, mid, ql, qr);
		auto right = getMin(node * 2 + 1, mid + 1, r, ql, qr);
		return min(left, right);
	}
};

vector<int> solution() {
	vector<int> res;

	SegmentTree smt;
	for (int i = 0; i < m; i++) {
		auto& cur = querys[i];

		if (get<0>(cur) == 1)
			smt.updateTree(1, 1, n, get<1>(cur), get<2>(cur));
		else
			res.push_back(smt.getMin(1, 1, n, get<1>(cur), get<2>(cur)).second);
	}

	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
	}

	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		querys[i] = make_tuple(a, b, c);
	}

	for (int ans : solution())
		cout << ans << '\n';

	return 0;
}