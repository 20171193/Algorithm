// ���� 13275�� : ���� �� �Ӹ���� �κ� ���ڿ�
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string str;
int solution()
{
	int maxLength = 0;

	// ����ó �˰���
	// Ȧ�� ���ڿ��� ����
	string manStr = "!#";
	for (char c : str)
	{
		manStr += c;
		manStr += '#';
	}
	manStr += '@'; // ���׸�Ʈ
	int size = manStr.size();

	vector<int> rads(size, 0);
	int c = 0,  // �߽�
		r = 0;  // ����

	// abcba
	for (int i = 1; i < size - 1; i++)
	{
		int opp = 2 * c - i;

		if (i < r)
			rads[i] = min(r - i, rads[opp]);

		// i �߽� Ȯ��
		while (manStr[i + (1 + rads[i])] == manStr[i - (1 + rads[i])])
			rads[i]++;

		// �߽� ����
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