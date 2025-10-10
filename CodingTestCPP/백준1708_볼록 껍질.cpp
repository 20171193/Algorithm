// ���� 1708�� : ���� ����

// �׶��� ��ĵ �˰���
//  1. y��ǥ�� ���� ���� ���� ���������� ���� (*���� �������� �� ��)
//  2. ������ ���� ������ ������ ����
//   2-1. ��ȸ�� : ���� ������ ����(���� push)
//   2-2. ��ȸ�� : ���� ���� (���� pop)
//  3. ���ÿ� �����ϴ� ���� ��� ���� �����ϴ� ���ϲ���
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
int n;

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

int solution(vector<pair<ll, ll>>& vec)
{
	// y��ǥ�� ����
	sort(vec.begin(), vec.end()
		, [](const pair<ll, ll>& a, const pair<ll, ll>& b)
		{
			if (a.second == b.second)
				return a.first < b.first;
			return a.second < b.second;
		});

	auto const& basePos = vec[0];
	// ������ �� ����
	sort(vec.begin() + 1, vec.end(),
		[basePos](const pair<ll, ll>& a, const pair<ll, ll>& b)
		{
			pair<ll, ll> da = TowardVector(basePos, a);
			pair<ll, ll> db = TowardVector(basePos, b);
			ll cross = Cross(da, db);

			// ���� �� : ũ�� ��
			if (cross == 0)
				return sqrMagnitude(da) < sqrMagnitude(db);

			// ���� ��
			return cross > 0;
		});

	// �׶��� ��ĵ �˰���
	vector<pair<ll, ll>> hull;
	hull.push_back(vec[0]);
	hull.push_back(vec[1]);
	for (int i = 2; i < vec.size(); i++)
	{
		while (hull.size() >= 2)
		{
			auto a = hull[hull.size() - 2];
			auto b = hull[hull.size() - 1];
			auto c = vec[i];

			auto ab = TowardVector(a, b);
			auto bc = TowardVector(b, c);
			if (Cross(ab, bc) > 0) break; // ��ȸ��
			hull.pop_back();	// ��ȸ�� ����
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
	if (n == 3)
	{
		cout << n << '\n';
		return 0;
	}

	vector<pair<ll, ll>> vec(n);
	for (int i = 0; i < n; i++)
		cin >> vec[i].first >> vec[i].second;

	std::cout << solution(vec) << '\n';
	return 0;
}