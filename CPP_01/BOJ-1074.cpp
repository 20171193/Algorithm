// 백준 1074번 Z

#include <iostream>
#include <math.h>
using namespace std;
int n, r, c, ret;
bool isFind;
void go(int y, int x, int edge)
{
	if (isFind)
		return;
	if (edge == 1)
	{
		if (r == y && x == c)
			isFind = true;
		ret++;
		return;
	}

	// 현재 depth에 없을 경우
	if (r < y || r >= y + edge || c < x || c >= x + edge)
	{
		// 목표 지점보다 현재 depth가 낮을 경우
		if (r >= y + edge || c >= x + edge)
			ret += pow(edge, 2);
		return;
	}

	int half = edge / 2;
	// 2사분면
	go(y, x, half);
	// 1사분면
	go(y, x + half, half);
	// 3사분면
	go(y + half, x, half);
	// 4사분면
	go(y + half, x + half, half);
}

int main()
{

	cin >> n >> r >> c;

	go(0, 0, pow(2, n));
	cout << ret - 1 << '\n';

	return 0;
}