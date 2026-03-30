// 백준 17386번 선분 교차1
#include <iostream>
using namespace std;

typedef long long ll;

#define y1 a
#define y2 aa
#define y3 aaa
#define y4 aaaa

float x1, x2, x3, x4, y1, y2, y3, y4;

ll GetCross(int _x1, int _y1, int _x2, int _y2)
{
	return (ll)_x1 * _y2 - (ll)_x2 * _y1;
}

bool IsInLine(int _x1, int _y1, int _x2, int _y2, int x, int y)
{
	return min(_x1, _x2) <= x && max(_x1, _x2) >= x && min(_y1, _y2) <= y && max(_y1, _y2) >= y;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> x1 >> y1 >> x2 >> y2
		>> x3 >> y3 >> x4 >> y4;

	// 1 2 3 4
	// A B C D
	// 외적을 통한 위치 판별
	ll abac = GetCross(x2 - x1, y2 - y1, x3 - x1, y3 - y1);	// AB X AC
	ll abad = GetCross(x2 - x1, y2 - y1, x4 - x1, y4 - y1); // AB X AD
	ll cdca = GetCross(x4 - x3, y4 - y3, x1 - x3, y1 - y3); // CD X CA
	ll cdcb = GetCross(x4 - x3, y4 - y3, x2 - x3, y2 - y3); // CD X CB

	// 각 정점이 서로의 양쪽에 위치하는 경우
	if (abac * abad < 0 && cdca * cdcb < 0)
		cout << 1 << '\n';
	else if (abac == 0 && IsInLine(x1, y1, x2, y2, x3, y3))
		cout << 1 << '\n';
	else if (abad == 0 && IsInLine(x1, y1, x2, y2, x4, y4))
		cout << 1 << '\n';
	else if (cdca == 0 && IsInLine(x3, y3, x4, y4, x1, y1))
		cout << 1 << '\n';
	else if (abad == 0 && IsInLine(x3, y3, x4, y4, x2, y2))
		cout << 1 << '\n';
	else
		cout << 0 << '\n';


	return 0;

}