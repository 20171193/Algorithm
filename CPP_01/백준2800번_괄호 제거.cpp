// 백준 2800번 : 괄호 제거 (https://www.acmicpc.net/problem/2800)
// 1. 괄호 쌍 비트마스킹
// 실패 케이스 : ((abc)) --> (abc), (abc) 중복
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>
using namespace std;

vector<string> solution(const string& str)
{
	string origin = str;

	// 괄호 인덱스 매핑
	vector<pair<int, int>> blankIndex;
	stack<int> blanks;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != '(' && str[i] != ')') continue;

		if (str[i] == '(')
			blanks.push(i);
		else if (str[i] == ')')
		{
			int start = blanks.top();
			blanks.pop();

			blankIndex.push_back({ start, i });
		}
	}

	int blankCount = blankIndex.size();
	vector<bool> isErased(str.size(), false);
	unordered_set<string> checkString;
	vector<string> answer;
	for (int i = 1; i < (1 << blankCount); i++)
	{
		for (int j = 0; j < blankCount; j++)
		{
			if (i & (1 << j))
			{
				isErased[blankIndex[j].first] = true;
				isErased[blankIndex[j].second] = true;
			}
		}

		string result = "";
		for (int j = 0; j < str.size(); j++)
		{
			if (!isErased[j])
				result += str[j];
		}

		if (checkString.find(result) == checkString.end())
		{
			checkString.insert(result);
			answer.push_back(result);
		}

		fill(isErased.begin(), isErased.end(), false);
	}

	sort(answer.begin(), answer.end());
	return answer;
}

int main()
{
	string str;
	cin >> str;

	for (const string& ans : solution(str))
		cout << ans << '\n';
	return 0;
}