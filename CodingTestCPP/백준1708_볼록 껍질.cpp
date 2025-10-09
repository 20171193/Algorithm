// 백준 1708번 : 볼록 껍질

// 그라함 스캔 알고리즘
//  1. y좌표가 가장 작은 값을 기준점으로 설정 (*볼록 껍질위의 한 점)
//  2. 기준점 부터 나머지 점들을 외적
//   2-1. 좌회전 : 볼록 껍질을 형성(스택 push)
//   2-2. 우회전 : 오목 껍질 (스택 pop)
//  3. 스택에 존재하는 점은 모든 점을 포함하는 볼록껍질
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
constexpr ll MAX_RANGE = 40001;

int n;
pair<ll, ll> basePos = { MAX_RANGE, MAX_RANGE };

ll Cross(const pair<ll, ll>& a, const pair<ll, ll>& b)
{
	return a.first * b.second - a.second * b.first;
}
ll sqrMagnitude(const pair<ll, ll>& a)
{
	return a.first * a.first + a.second * a.second;
}
pair<ll, ll> TowardVector(const pair<ll, ll>& from, const pair<ll, ll>& to)
{
	return { to.first - from.first, to.second - from.second };
}
bool comp(const pair<ll, ll>& a, const pair<ll, ll>& b)
{
	pair<ll, ll> da = TowardVector(basePos, a);
	pair<ll, ll> db = TowardVector(basePos, b);
	ll cross = Cross(da, db);

	if (cross == 0)
		return sqrMagnitude(da) < sqrMagnitude(db);
	return cross > 0;
}
int solution(vector<pair<ll, ll>>& vec)
{
	// 기준점 각 정렬
	sort(vec.begin(), vec.end(), comp);

	// 그라함 스캔 알고리즘
	vector<pair<ll, ll>> hull;
	hull.push_back(basePos);
	hull.push_back(vec[0]);
	for (int i = 1; i < vec.size(); i++)
	{
		while (hull.size() >= 2)
		{
			auto a = hull[hull.size() - 2];
			auto b = hull[hull.size() - 1];
			auto c = vec[i];

			auto ab = TowardVector(a, b);
			auto bc = TowardVector(b, c);
			if (Cross(ab, bc) > 0) break; // 좌회전
			hull.pop_back();	// 우회전 제거
		}
		hull.push_back(vec[i]);
	}

	return hull.size();
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	vector<pair<ll, ll>> vec;

	for (int i = 0; i < n; i++)
	{
		ll x, y;
		cin >> x >> y;
		if (y < basePos.second)
		{
			if (basePos.first != MAX_RANGE)
				vec.push_back({ x, y });
			basePos = { x,y };
		}
		else
			vec.push_back({ x,y });
	}

	std::cout << solution(vec) << '\n';
	return 0;
}