// 백준 1517번 : 버블 소트
// 조건
// 1. N(1<=N<=500,000)개로 이루어진 수열에 대해 버블 소트를 수행할 때,
//    Swap이 발생하는 횟수 출력
// 2. 0 <= A[i] <= 10^9
// 풀이
// 1. Swap조건 : 0~i까지 A[i]보다 큰 수의 개수
// 2. 구간합 세그먼트 트리
//    => 범위 매핑
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
constexpr ll INF = 1000000001;

int n;
ll arr[500001];

struct SegmentTree {
	int size;
	vector<ll> tree;

	SegmentTree(int size) : size(size) {
		tree.assign(size * 4, 0);
	}

	void update(int node, int l, int r, int idx) {
		if (l == r) {
			tree[node]++;
			return;
		}

		int mid = (l + r) >> 1;
		if (idx <= mid) update(node * 2, l, mid, idx);
		else update(node * 2 + 1, mid + 1, r, idx);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	ll query(int node, int l, int r, int ql, int qr) {
		if (ql > r || qr < l) return 0;
		if (l <= ql && qr <= r) return tree[node];

		int mid = (l + r) >> 1;
		return query(node * 2, l, mid, ql, qr) + query(node * 2 + 1, mid + 1, r, ql, qr);
	}
};

ll solution() {
	// 좌표 압축 (인덱스 매핑)
	vector<ll> comp(arr, arr + n);
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());

	// 1based
	for (int i = 0; i < n; i++)
		arr[i] = lower_bound(comp.begin(), comp.end(), arr[i]) - comp.begin() + 1;

	SegmentTree smt(comp.size());
	ll res = 0;
	for (int i = 0; i < n; i++) {
		// arr[i]보다 큰 구간 합
		res += smt.query(1, 1, comp.size(), arr[i] + 1, comp.size());
		// 노드 추가
		smt.update(1, 1, comp.size(), arr[i]);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	cout << solution() << '\n';
	return 0;
}