// 백준11505번 : 구간 곱 구하기
// 세그먼트 트리
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MOD = 1'000'000'007;

struct SegmentTree
{
	int _n;
	vector<tuple<int, int, int>> tree;
	SegmentTree(int n)
	{
		tree.assign(n * 4, make_tuple(0, 0, 0));
		_n = n;
	}
	int MakeTree(int i, int l, int r, const vector<int>& arr)
	{
		if (l == r)
		{
			tree[i] = make_tuple(arr[l], 1, arr[l]);
			return arr[l];
		}
		int mid = (l + r) >> 1;
		ll leftMTP = MakeTree(i * 2, l, mid, arr);
		if (leftMTP != 0) leftMTP %= MOD;
		ll rightMTP = MakeTree(i * 2 + 1, mid + 1, r, arr);
		if (rightMTP != 0) rightMTP %= MOD;
		ll mtp = leftMTP * rightMTP;
		if (mtp != 0) mtp %= MOD;

		tree[i] = make_tuple((int)leftMTP, (int)rightMTP, (int)mtp);
		return get<2>(tree[i]);
	}
	int GetPrefixMTP(int i, int l, int r, int ql, int qr)
	{
		if (ql > r || qr < l) return 1;	// 곱하기 예외
		if (ql <= l && r <= qr) return get<2>(tree[i]);

		int mid = (l + r) >> 1;
		ll leftMTP = GetPrefixMTP(i * 2, l, mid, ql, qr);
		if (leftMTP != 0) leftMTP %= MOD;
		ll rightMTP = GetPrefixMTP(i * 2 + 1, mid + 1, r, ql, qr);
		if (rightMTP != 0) rightMTP %= MOD;
		ll mtp = leftMTP * rightMTP;
		if (mtp != 0) mtp %= MOD;

		return (int)(mtp);
	}
	int UpdateTree(int i, int l, int r, int updateIndex, int updateValue)
	{
		if (l == r && l == updateIndex)
		{
			tree[i] = make_tuple(updateValue, 1, updateValue);
			return updateValue;	// 값 갱신
		}

		int mid = (l + r) >> 1;

		if (l <= updateIndex && updateIndex <= mid)
		{
			// 갱신된 서브트리만 확인 (n/2)
			ll leftMTP = UpdateTree(i * 2, l, mid, updateIndex, updateValue);
			if (leftMTP != 0) leftMTP %= MOD;
			if (leftMTP != (ll)get<0>(tree[i]))
			{
				ll mtp = leftMTP * get<1>(tree[i]);
				if (mtp != 0) mtp %= MOD;
				tree[i] = make_tuple((int)leftMTP, get<1>(tree[i]), (int)mtp);
				return (int)mtp;
			}
		}

		if (mid + 1 <= updateIndex && updateIndex <= r)
		{
			// 갱신된 서브트리만 확인 (n/2)
			ll rightMTP = UpdateTree(i * 2 + 1, mid + 1, r, updateIndex, updateValue);
			if (rightMTP != 0) rightMTP %= MOD;
			if (rightMTP != (ll)get<1>(tree[i]))
			{
				ll mtp = get<0>(tree[i]) * rightMTP;
				if (mtp != 0) mtp %= MOD;
				tree[i] = make_tuple(get<0>(tree[i]), (int)rightMTP, (int)mtp);
				return (int)mtp;
			}
		}
		return get<2>(tree[i]);
	}
};

vector<int> solution(int n, const vector<int>& arr, const vector<tuple<int, int, int>>& oper)
{
	vector<int> result;

	SegmentTree sgmTree(n);
	sgmTree.MakeTree(1, 1, n, arr);

	for (auto& op : oper)
	{
		// 값 변경
		if (get<0>(op) == 1)
			sgmTree.UpdateTree(1, 1, n, get<1>(op), get<2>(op));
		// 출력
		else
			result.push_back(sgmTree.GetPrefixMTP(1, 1, n, get<1>(op), get<2>(op)));
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input
	int n = 0, m = 0, k = 0;
	cin >> n >> m >> k;
	vector<int> arr(n + 1);	// 1-based
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	vector<tuple<int, int, int>> opers(m + k);
	for (int i = 0; i < m + k; i++)
	{
		int a = 0, b = 0, c = 0;
		cin >> a >> b >> c;
		opers[i] = make_tuple(a, b, c);
	}

	// output
	for (int ans : solution(n, arr, opers))
		cout << ans << '\n';

	return 0;
}