// น้มุ 23971น๘ ZOAC 4
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	int h, w, n, m;
	cin >> h >> w >> n >> m;
	int row = (int)(ceil((float)h / (n + 1)));
	int col = (int)(ceil((float)w / (m + 1)));
	cout << row * col << '\n';
	return 0;
}