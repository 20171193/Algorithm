// 백준10868번 : 최솟값
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int INF = 1'000'000'001;

struct SegmentTree
{
	int _size;
	vector<int> _tree;

	SegmentTree(int size)
	{
		_tree.assign(size * 4, 0);
		_size = size;
	}

	int MakeTree(int i, int l, int r, const vector<int>& arr)
	{
		if (l == r) return _tree[i] = arr[l];

		int mid = (l + r) >> 1;
		int lMin = MakeTree(i * 2, l, mid, arr);
		int rMin = MakeTree(i * 2 + 1, mid + 1, r, arr);
		return _tree[i] = min(lMin, rMin);
	}

	// ql, qr : 구간 인덱스
	int GetMinValue(int i, int l, int r, int ql, int qr)
	{
		if (qr < l || r < ql) return INF;
		if (ql <= l && r <= qr) return _tree[i];

		int mid = (l + r) >> 1;
		int lMin = GetMinValue(i * 2, l, mid, ql, qr);
		int rMin = GetMinValue(i * 2 + 1, mid + 1, r, ql, qr);
		return min(lMin, rMin);
	}
};

vector<int> solution(int n, const vector<int>& arr, const vector<pair<int, int>>& range)
{
	vector<int> result;

	SegmentTree segTree(n);
	segTree.MakeTree(1, 1, n, arr);

	for (auto& r : range)
		result.push_back(segTree.GetMinValue(1, 1, n, r.first, r.second));

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

	vector<int> arr(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	vector<pair<int, int>> range(m);
	for (int i = 0; i < m; i++)
		cin >> range[i].first >> range[i].second;

	// output
	for (int ans : solution(n, arr, range))
		cout << ans << '\n';

	return 0;
}