// 백준 4354번 : 문자열 제곱
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// s = a^n을 만족하는 가장 큰 n
// 1. 패턴 문자열 찾기
// 2. 패턴 문자열 반복횟수
int solution(const string& str)
{
	int result = 1;
	int size = str.size();
	vector<int> pl(size, 0);	// kmp(pattern length)
	for (int j = 0, i = 1; i < size; i++)
	{
		while (j > 0 && str[i] != str[j])
			j = pl[j - 1];

		if (str[i] == str[j])
			pl[i] = ++j;
	}

	int patternLength = size - pl[size - 1];

	if (size % patternLength == 0)
		return size / patternLength;
	else
		return 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	vector<int> answer;
	string str = "";

	while (1)
	{
		getline(cin, str);
		if (str == ".") break;
		answer.push_back(solution(str));
	}

	for (int ans : answer)
		cout << ans << '\n';

	return 0;
}