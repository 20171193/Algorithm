// 백준  1002번 터렛

#include <iostream>
#include <math.h>
using namespace std;
#define _y1 aaa

int t, _x1, _x2, _y1, _y2, _r1, _r2;

float GetDist()
{
	return sqrt(pow((_x2 - _x1), 2) + pow((_y2 - _y1), 2));
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;
	while (t--)
	{
		cin >> _x1 >> _y1 >> _r1 >> _x2 >> _y2 >> _r2;
		int rSum = _r1 + _r2;
		int rDif = abs(_r1 - _r2);
		float dist = GetDist();

		// 두점
		if (rDif < dist && rSum > dist)
			cout << 2 << '\n';
		// 한점
		else if ((dist != 0) && (rDif == dist || rSum == dist))
			cout << 1 << '\n';
		// 같은 원
		else if (dist == 0 && _r1 == _r2)
			cout << -1 << '\n';
		else
			cout << 0 << '\n';
	}
	return 0;
}
