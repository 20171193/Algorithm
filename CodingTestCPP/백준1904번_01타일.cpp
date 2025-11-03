// 백준 1904번 : 01타일
#include <iostream>
#include <vector>
using namespace std;

int n;

int main()
{
	cin >> n;
	if (n <= 2)
	{
		cout << n << '\n';
		return 0;
	}

	vector<int> fibo(n + 1);
	fibo[1] = 1;
	fibo[2] = 2;
	for (int i = 3; i <= n; i++)
		fibo[i] = (fibo[i - 2] + fibo[i - 1]) % 15746;

	cout << fibo[n] << '\n';
	return 0;
}