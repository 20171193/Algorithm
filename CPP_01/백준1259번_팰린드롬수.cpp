// 백준 1259번 팰린드롬수
#include <iostream>
using namespace std;

int main()
{
	string temp = "";
	do
	{
		cin >> temp;
		if (temp[0] == '0')
			break;

		int halfIndex = temp.length() % 2 ? temp.length() / 2 + 1 : temp.length() / 2;
		int halfCount = temp.length() / 2;
		string rTemp = temp.substr(halfIndex, halfCount);
		reverse(rTemp.begin(), rTemp.end());

		if (temp.substr(0, halfCount) == rTemp)
			cout << "yes\n";
		else
			cout << "no\n";
	} while (temp[0] != '0');

	return 0;
}