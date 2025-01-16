// น้มุ 15829น๘ Hashing
#include <iostream>
#include <math.h>
using namespace std;

typedef long long ll;
const ll r = 31;
const int M = 1234567891;

int main()
{
	int l;
	string s;
	cin >> l >> s;
	ll sum = 0;
	for (int i = 0; i < s.size(); i++)
		sum += (s[i] - 'a' + 1) * pow(r, i);

	cout << sum % M << '\n';
	return 0;
}