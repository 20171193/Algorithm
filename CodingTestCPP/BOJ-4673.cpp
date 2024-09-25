// 백준 4673번 셀프 넘버

#include <iostream>
using namespace std;

bool num[10002];

int main()
{
	for (int i = 1; i < 10001; i++)
	{
		int m_num = i;
		int temp = i;
		while (temp > 0)
		{
			m_num += (temp % 10);
			temp /= 10;
		}
		num[m_num] = true;
	}

	for (int i = 1; i < 10001; i++)
	{
		if (!num[i])
			cout << i << '\n';
	}

	return 0;
}