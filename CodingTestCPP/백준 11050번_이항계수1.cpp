// 백준 11050번 이항 계수1 

#include <iostream>
using namespace std;

int n, k, fac[11];

int Factorial(int num)
{
	if (fac[num]) return fac[num];

	int ret = 2;
	for (int i = 3; i <= num; i++)
	{
		ret *= i;
		fac[i] = ret;
	}
	return ret;
}

int main()
{
	cin >> n >> k;

	fac[0] = 0;
	fac[1] = 1;
	fac[2] = 2;

	if (k == 0 || n == k)
		cout << 1 << '\n';
	else
		cout << (int)(Factorial(n) / (Factorial(n - k) * Factorial(k)));
	return 0;
}