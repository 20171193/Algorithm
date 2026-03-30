//백준 1027번 : 고층 건물
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

// 외적
int n, answer = -1, arr[51];

ll Cross(ll ax, ll ay, ll bx, ll by, ll cx, ll cy)
{
	ll abx = bx - ax, aby = by - ay
		, acx = cx - ax, acy = cy - ay;
	return abx * acy - aby * acx;
}

// *각 인덱스에서 좌측/우측 건물들을 확인
//  *좌측 : X좌표는 감소. 즉, 우회전을 카운팅
//  *우측 : X좌표는 증가. 즉, 좌회전을 카운팅
int VisibleCount(int index)
{
	int count = 0;

	int ax = index, ay = arr[index],
		bx = index - 1, by = 0,
		cx = 0, cy = 0;

	// 왼쪽 확인
	if (bx >= 0)
	{
		count++;
		by = arr[bx];
		cx = bx - 1;
		while (cx >= 0)
		{
			cy = arr[cx];
			ll d = Cross(ax, ay, bx, by, cx, cy);
			// 우회전만 카운팅
			if (d < 0)
			{
				count++;
				bx = cx;
				by = cy;
			}
			cx--;
		}
	}

	// 좌표 초기화
	ax = index;
	ay = arr[index];
	bx = index + 1;
	// 오른쪽 확인
	if (bx <= n - 1)
	{
		count++;
		by = arr[bx];
		cx = bx + 1;
		while (cx < n)
		{
			cy = arr[cx];
			ll d = Cross(ax, ay, bx, by, cx, cy);
			// 좌회전만 카운팅
			if (d > 0)
			{
				count++;
				bx = cx;
				by = cy;
			}
			cx++;
		}
	}
	return count;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int i = 0; i < n; i++)
		answer = max(VisibleCount(i), answer);

	cout << answer << '\n';
	return 0;
}