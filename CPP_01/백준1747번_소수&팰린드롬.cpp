// 백준1747번 소수&팰린드롬
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
using namespace std;

const int MAX_VALUE = 2000001;
int n;
bool nonPrime[MAX_VALUE];

void SetPrime()
{
	for (int i = 2; i * i <= MAX_VALUE; i++)
		if (!nonPrime[i])
			for (int j = i * i; j <= MAX_VALUE; j += i)
				nonPrime[j] = true;
}
bool IsPalindrome(int num)
{
	string s = to_string(num);
	string rev = s;
	reverse(rev.begin(), rev.end());

	return s == rev;
}

int main()
{
	cin >> n;

	nonPrime[1] = true;
	SetPrime();

	for (int i = n; i <= MAX_VALUE; i++)
	{
		if (!nonPrime[i])
		{
			if (IsPalindrome(i))
			{
				cout << i << '\n';
				break;
			}
		}
	}

	return 0;
}// 백준1747번 소수&팰린드롬
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
using namespace std;

const int MAX_VALUE = 2000001;
int n;
bool nonPrime[MAX_VALUE];

void SetPrime()
{
	for (int i = 2; i * i <= MAX_VALUE; i++)
		if (!nonPrime[i])
			for (int j = i * i; j <= MAX_VALUE; j += i)
				nonPrime[j] = true;
}
bool IsPalindrome(int num)
{
	string s = to_string(num);
	string rev = s;
	reverse(rev.begin(), rev.end());

	return s == rev;
}

int main()
{
	cin >> n;

	nonPrime[1] = true;
	SetPrime();

	for (int i = n; i <= MAX_VALUE; i++)
	{
		if (!nonPrime[i])
		{
			if (IsPalindrome(i))
			{
				cout << i << '\n';
				break;
			}
		}
	}

	return 0;
}