// 백준 1735번 - 분수 합
#include <iostream>
using namespace std;

// 최대 공약수
int GetGCD(int a, int b)
{
	int c = a % b;
	if (c == 0)
		return b;
	return GetGCD(b, c);
}

int main()
{
	int aBot, aTop, bBot, bTop, cBot, cTop, getZero = 0;
	cin >> aTop >> aBot >> bTop >> bBot;

	if (!aTop || !aBot)
	{
		aTop = aBot = 0;
		getZero = -1;
	}
	if (!bTop || !bBot)
	{
		bTop = bBot = 0;
		getZero = 1;
	}

	if (getZero != 0)
	{
		int gcd = getZero < 0 ? GetGCD(bTop, bBot) : GetGCD(aTop, aBot);
		cout << (getZero < 0 ? bTop / gcd : aTop / gcd) << ' '
			<< (getZero < 0 ? bBot / gcd : aBot / gcd) << '\n';
	}
	else
	{
		cTop = aTop * bBot + bTop * aBot;
		cBot = aBot * bBot;
		int gcd = GetGCD(cTop, cBot);
		cout << cTop / gcd << ' ' << cBot / gcd << '\n';
	}

	return 0;
}