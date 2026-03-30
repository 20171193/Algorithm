// 백준1509번 : 팰린드롬 분할
#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
using namespace std;

constexpr int MAX_LENGTH = 2501;

string str;
bool isPal[MAX_LENGTH][MAX_LENGTH];
int divCount[MAX_LENGTH];

int solution()
{
	int n = str.size();

	// 팰린드롬 확인
	// 길이 1
	for (int i = 0; i < n; i++)
		isPal[i][i] = true;

	// 길이 2
	for (int i = 1; i < n; i++)
		if (str[i] == str[i - 1])
			isPal[i - 1][i] = true;

	// 길이 3이상
	for (int len = 3; len <= n; len++)
	{
		for (int start = 0; start < n - len + 1; start++)
		{
			int end = start + len - 1;
			if (str[start] == str[end] && isPal[start + 1][end - 1])
				isPal[start][end] = true;
		}
	}

	for (int end = 1; end <= n; end++)
	{
		divCount[end] = MAX_LENGTH;
		for (int start = 0; start <= end; start++)
		{
			if (isPal[start][end])
				divCount[end] = min(divCount[end], divCount[start - 1] + 1);
		}
	}

	return divCount[n - 1];
}

int main()
{
	cin >> str;
	cout << solution() << '\n';
	return 0;
}