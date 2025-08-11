// 백준 2042번 : 구간 합 구하기
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

typedef long long ll;

#pragma region 세그먼트 트리 메서드
//ll MakeSegmentTree(int node, int l, int r, vector<ll>& tree, const vector<ll>& vec)
//{
//	if (l == r) return tree[node] = vec[l];
//	int mid = (l + r) >> 1;
//	ll leftSum = MakeSegmentTree(node * 2, l, mid, tree, vec);
//	ll rightSum = MakeSegmentTree(node * 2 + 1, mid + 1, r, tree, vec);
//	return tree[node] = leftSum + rightSum;
//}
//
//ll ChangeNum(int node, int l, int r, int index, ll value, vector<ll>& tree)
//{
//	if (index < l || index > r)
//		return tree[node];
//
//	if (l == r)
//		return tree[node] = value;
//
//	int mid = (l + r) >> 1;
//
//	ll leftSum = ChangeNum(node * 2, l, mid, index, value, tree);
//	ll rightSum = ChangeNum(node * 2 + 1, mid + 1, r, index, value, tree);
//
//	// 트리 갱신
//	return tree[node] = leftSum + rightSum;
//}
//
//// 구간합 출력
//ll PrefixSum(int node, int l, int r, int ql, int qr, vector<ll>& tree)
//{
//	if (ql > r || qr < l)
//		return 0;
//	// 구간 포함
//	if (ql <= l && qr >= r)
//		return tree[node];
//
//	int mid = (l + r) >> 1;
//	ll leftSum = PrefixSum(node * 2, l, mid, ql, qr, tree);
//	ll rightSum = PrefixSum(node * 2 + 1, mid + 1, r, ql, qr, tree);
//	return leftSum + rightSum;
//}
#pragma endregion

#pragma region 팬윅 트리 메서드
void Update(int i, ll value, vector<ll>& tree)
{
	while (i <= tree.size()-1)
	{
		tree[i] += value;
		// 우측 끝 비트 추가
		i += i & (-i);
	}
}

void ChangeNum(int i, ll targetValue, vector<ll>& tree, vector<ll>& nums)
{
	ll diff = targetValue - nums[i];
	nums[i] = targetValue;
	Update(i + 1, diff, tree);
}

ll PrefixSum(int i, const vector<ll>& tree)
{
	ll sum = 0;
	while (i > 0)
	{
		sum += tree[i];
		i -= i & (-i);
	}
	return sum;
}
#pragma endregion 

vector<ll> solution(vector<ll>& nums, const vector<tuple<int, int, ll>> opers)
{
	vector<ll> result;
	int n = nums.size();
#pragma region 세그먼트 트리 풀이
	//vector<ll> segmentTree(n * 4);
	//MakeSegmentTree(1, 0, n - 1, segmentTree, nums);

	//for (auto& oper : opers)
	//{
	//	int operNum = get<0>(oper);
	//	// 값 수정
	//	if (operNum == 1)
	//	{
	//		int targetIndex = get<1>(oper) - 1;
	//		ll targetNum = get<2>(oper);
	//		ChangeNum(1, 0, n - 1, targetIndex, targetNum, segmentTree);
	//	}
	//	// 합 출력
	//	else // operNum == 2 
	//	{
	//		int startIndex = get<1>(oper) - 1;
	//		int endIndex = (int)get<2>(oper) - 1;
	//		result.push_back(PrefixSum(1, 0, n - 1, startIndex, endIndex, segmentTree));
	//	}
	//}
#pragma endregion 

#pragma region 팬윅 트리 풀이
	vector<ll> fenwickTree(n + 1); // 1-based

	for (int i = 1; i <= n; i++)
		Update(i, nums[i], fenwickTree);

	for (auto& oper : opers)
	{
		int operNum = get<0>(oper);
		// 값 수정
		if (operNum == 1)
		{
			int targetIndex = get<1>(oper);
			ll targetNum = get<2>(oper);
			ChangeNum(targetIndex, targetNum, fenwickTree, nums);
		}
		// 합 출력
		else // operNum == 2 
		{
			int startIndex = get<1>(oper);
			int endIndex = (int)get<2>(oper);
			result.push_back(PrefixSum(endIndex, fenwickTree) 
				- PrefixSum(startIndex - 1, fenwickTree));
		}
	}

#pragma endregion
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 0, m = 0, k = 0;

	// input
	cin >> n >> m >> k;
	vector<ll> nums(n);
	vector<tuple<int, int, ll>> opers(m + k);
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	for (int i = 0; i < m + k; i++)
	{
		int operNum = 0, index = 0;
		ll value = 0;
		cin >> operNum >> index >> value;
		opers[i] = make_tuple(operNum, index, value);
	}

	// output
	for (ll ans : solution(nums, opers))
		cout << ans << '\n';
	return 0;
}