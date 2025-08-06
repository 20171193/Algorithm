// 백준 13275번 : 가장 긴 팰린드롬 부분 문자열
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string str;
int solution()
{
	int maxLength = 0;

	// 마나처 알고리즘
	// 홀수 문자열로 변경
	string manStr = "!#";
	for (char c : str)
	{
		manStr += c;
		manStr += '#';
	}
	manStr += '@'; // 세그먼트
	int size = manStr.size();

	vector<int> rads(size, 0);
	int c = 0,  // 중심
		r = 0;  // 우측

	// abcba
	for (int i = 1; i < size - 1; i++)
	{
		int opp = 2 * c - i;

		if (i < r)
			rads[i] = min(r - i, rads[opp]);

		// i 중심 확장
		while (manStr[i + (1 + rads[i])] == manStr[i - (1 + rads[i])])
			rads[i]++;

		// 중심 갱신
		if (i + rads[i] > r)
		{
			c = i;
			r = i + rads[i];
		}
	}

	return *max_element(rads.begin(), rads.end());
}

int main()
{
	cin >> str;
	cout << solution() << '\n';
	return 0;
}