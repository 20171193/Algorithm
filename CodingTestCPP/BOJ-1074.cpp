// ���� 1074�� Z

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

	// ���� depth�� ���� ���
	if (r < y || r >= y + edge || c < x || c >= x + edge)
	{
		// ��ǥ �������� ���� depth�� ���� ���
		if (r >= y + edge || c >= x + edge)
			ret += pow(edge, 2);
		return;
	}

	int half = edge / 2;
	// 2��и�
	go(y, x, half);
	// 1��и�
	go(y, x + half, half);
	// 3��и�
	go(y + half, x, half);
	// 4��и�
	go(y + half, x + half, half);
}

int main()
{

	cin >> n >> r >> c;

	go(0, 0, pow(2, n));
	cout << ret - 1 << '\n';

	return 0;
}