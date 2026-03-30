// 백준 17387번 : 선분 교차 2
#include <iostream>
using namespace std;

typedef long long ll;

pair<ll, ll> p1, p2, p3, p4;

pair<ll, ll> GetVector2(const pair<ll, ll>& s, const pair<ll, ll>& e)
{
	return { e.first - s.first, e.second - s.second };
}

int Cross(const pair<ll, ll>& v1, const pair<ll, ll>& v2)
{
	ll res = v1.first * v2.second - v1.second * v2.first;
	if (res < 0)
		return -1;
	else if (res > 0)
		return 1;
	else
		return 0;
}

bool OnSegment(const pair<ll, ll>& sp1, const pair<ll, ll>& sp2, const pair<ll, ll>& p)
{
	return p.first >= min(sp1.first, sp2.first) && p.first <= max(sp1.first, sp2.first)
		&& p.second >= min(sp1.second, sp2.second) && p.second <= max(sp1.second, sp2.second);
}

bool solve()
{
	pair<ll, ll> v12 = GetVector2(p1, p2);
	pair<ll, ll> v13 = GetVector2(p1, p3);
	pair<ll, ll> v14 = GetVector2(p1, p4);
	int c123 = Cross(v12, v13);
	int c124 = Cross(v12, v14);

	pair<ll, ll> v34 = GetVector2(p3, p4);
	pair<ll, ll> v31 = GetVector2(p3, p1);
	pair<ll, ll> v32 = GetVector2(p3, p2);
	int c341 = Cross(v34, v31);
	int c342 = Cross(v34, v32);

	// 평행
	if (c123 * c124 == 0 && c341 * c342 == 0)
	{
		// 한 점이라도 포함될 경우
		if (OnSegment(p1, p2, p3) || OnSegment(p1, p2, p4)
			|| OnSegment(p3, p4, p1) || OnSegment(p3, p4, p2))
			return true;
		return false;
	}

	// CCW
	return (c123 * c124 <= 0) && (c341 * c342 <= 0);
}

int main()
{
	cin >> p1.first >> p1.second
		>> p2.first >> p2.second
		>> p3.first >> p3.second
		>> p4.first >> p4.second;


	if (solve())
		cout << 1 << '\n';
	else
		cout << 0 << '\n';

	return 0;
}