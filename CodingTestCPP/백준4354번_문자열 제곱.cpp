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
	for (int len = 1; len <= size / 2; len++)
	{
		if (size % len != 0)
			continue;

		string pattern = str.substr(0, len);
		bool isSuccess = true;
		for (int j = len; j <= size - len; j += len)
		{
			if (pattern != str.substr(j, len))
			{
				isSuccess = false;
				break;
			}
		}

		if (isSuccess)
			result = max(result, size / len);
	}

	return result;
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