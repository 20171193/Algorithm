// 백준 2162번 : 선분 그룹
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int CCW(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
	pair<int, int> ab = { b.first - a.first, b.second - a.second };
	pair<int, int> ac = { c.first - a.first, c.second - a.second };
	int result = ab.second * ac.first - ab.first * ac.second;

	if (result > 0)
		return 1;
	else if (result < 0)
		return -1;
	else
		return 0;
}

struct Segment
{
	pair<int, int> ls, rs;
	bool IsCollision(const Segment& other) const
	{
		int abcd = CCW(ls, rs, other.ls) * CCW(ls, rs, other.rs);
		int cdab = CCW(other.ls, other.rs, ls) * CCW(other.ls, other.rs, rs);
		if (abcd <= 0 && cdab <= 0)
		{
			if (abcd == 0 && cdab == 0)
			{
				// 겹침 판단
				int abMinX = min(ls.first, rs.first), abMaxX = max(ls.first, rs.first);
				int cdMinX = min(other.ls.first, other.rs.first), cdMaxX = max(other.ls.first, other.rs.first);
				int abMinY = min(ls.second, rs.second), abMaxY = max(ls.second, rs.second);
				int cdMinY = min(other.ls.second, other.rs.second), cdMaxY = max(other.ls.second, other.rs.second);

				return !(abMaxX < cdMinX || abMinX > cdMaxX || abMaxY < cdMinY || abMinY > cdMaxY);
			}
			return true;
		}
		else
			return false;
	}
};

int n;
vector<int> ufSize, root;
vector<Segment> segments;

int Find(int a)
{
	if (a != root[a])
		root[a] = Find(root[a]);

	return root[a];
}

// union by size
void Union(int a, int b)
{
	int ra = Find(a);
	int rb = Find(b);
	if (ra == rb) return;

	if (ufSize[ra] >= ufSize[rb])
	{
		root[rb] = ra;
		ufSize[ra] += ufSize[rb];
		ufSize[rb] = 0;
	}
	else
	{
		root[ra] = rb;
		ufSize[rb] += ufSize[ra];
		ufSize[ra] = 0;
	}
}

int main()
{
	cin >> n;

	ufSize.assign(n, 1);
	root.assign(n, 0);
	iota(root.begin(), root.end(), 0);
	for (int i = 0; i < n; i++)
	{
		int lx, ly, rx, ry;
		cin >> lx >> ly >> rx >> ry;
		segments.push_back({ {lx, ly}, {rx,ry} });
	}

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (Find(i) == Find(j)) continue;
			if (!segments[i].IsCollision(segments[j])) continue;

			Union(i, j);
		}
	}

	int groupCount = 0;
	int maxSegments = 0;
	for (int i = 0; i < n; i++)
	{
		if (ufSize[i] > 0)
		{
			groupCount++;
			maxSegments = max(maxSegments, ufSize[i]);
		}
	}

	cout << groupCount << '\n';
	cout << maxSegments << '\n';

	return 0;
}