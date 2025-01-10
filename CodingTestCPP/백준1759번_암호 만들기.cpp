// 백준 1759번 : 암호 만들기
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const string vowel = "aeiou";

int l, c;
vector<char> vow, con;

bool IsVowel(char c)
{
	for (int i = 0; i < vowel.size(); i++)
		if (vowel[i] == c)
			return true;
	return false;
}

int main()
{
	cin >> l >> c;
	for (int i = 0; i < c; i++)
	{
		char c;
		cin >> c;

		if (IsVowel(c))
			vow.push_back(c);
		else
			con.push_back(c);
	}

	sort(vow.begin(), vow.end());
	sort(con.begin(), con.end());

	vector<string> answers;

	for (int i = 1; i < (1 << (vow.size() + con.size())); i++)
	{
		int totalCount = 0, vowCount = 0, conCount = 0;
		string temp = "";
		for (int j = 0; j < vow.size() + con.size(); j++)
		{
			if (i & (1 << j))
			{
				if (j < vow.size())
				{
					temp += vow[j];
					vowCount++;
				}
				else
				{
					temp += con[j - vow.size()];
					conCount++;
				}

				totalCount++;

				if (totalCount > l)
					break;
			}
		}

		if (totalCount != l || vowCount < 1 || conCount < 2)
			continue;

		sort(temp.begin(), temp.end());
		answers.push_back(temp);
	}

	sort(answers.begin(), answers.end());

	for (string ans : answers)
		cout << ans << '\n';

	return 0;
}