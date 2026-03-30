// 백준2357번 : 최솟값과 최댓값
// 세그먼트 트리
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INIT_MIN = 1'000'000'001, INIT_MAX = -1;

struct SegmentTree
{
	int _n;
	vector<pair<int, int>> tree;
	SegmentTree(int n)
	{
		tree.assign(n * 4, { 0,0 });
		_n = n;
	}
	pair<int, int> CalculatePair(const pair<int, int>& a, const pair<int, int>& b)
	{
		return make_pair(min({ a.first, b.first }), max({ a.second, b.second }));
	}
	pair<int, int> MakeTree(int i, int l, int r, const vector<int>& arr)
	{
		if (l == r)
			return tree[i] = make_pair(arr[l], arr[r]);
		int mid = (l + r) >> 1;
		auto lp = MakeTree(i * 2, l, mid, arr);
		auto rp = MakeTree(i * 2 + 1, mid + 1, r, arr);
		return tree[i] = CalculatePair(lp, rp);
	}
	pair<int, int> GetPair(int i, int l, int r, int ql, int qr)
	{
		if (ql > r || qr < l)
			return make_pair(INIT_MIN, INIT_MAX);
		if (ql <= l && r <= qr)
			return tree[i];
		int mid = (l + r) >> 1;
		auto lp = GetPair(i * 2, l, mid, ql, qr);
		auto rp = GetPair(i * 2 + 1, mid + 1, r, ql, qr);

		return CalculatePair(lp, rp);
	}
};

vector<pair<int, int>> solution(int n, int m, const vector<int>& arr, const vector<pair<int, int>>& range)
{
	vector<pair<int, int>> result;

	// 세그먼트 트리 구성
	SegmentTree sgmTree(n + 1);
	sgmTree.MakeTree(1, 1, n, arr);

	// 구간합
	for (auto& r : range)
		result.push_back(sgmTree.GetPair(1, 1, n, r.first, r.second));

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// input
	int n = 0, m = 0;
	cin >> n >> m;
	vector<int> arr(n + 1);	// 1-based
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	vector<pair<int, int>> range(m);
	for (int i = 0; i < m; i++)
		cin >> range[i].first >> range[i].second;

	// output
	for (auto& p : solution(n, m, arr, range))
		cout << p.first << ' ' << p.second << '\n';

	return 0;
}