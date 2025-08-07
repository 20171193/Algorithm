// ���� 4354�� : ���ڿ� ����
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// s = a^n�� �����ϴ� ���� ū n
// 1. ���� ���ڿ� ã��
// 2. ���� ���ڿ� �ݺ�Ƚ��
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