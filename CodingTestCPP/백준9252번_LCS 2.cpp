// ���� 9252�� : LCS2
// DP
//  - dp[i][j] : s1[0..i-1]�� s2[0..j-1]������ LCS ����(�ִ� ���� �κ� ���� ����)

// ������
//  - dp�� �������� ��ȸ�ϸ�, dp[i][j]�� dp[i-1][j-1]+1�� ���ŵ� ��ġ�� Ž��
//    -> �� ��ġ�� ���ڸ� LCS�� ����

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int ret;
string s1, s2, answer;

void solution()
{
	int s1Length = s1.size();
	int s2Length = s2.size();

	vector<vector<int>> dp(s1Length + 1, vector<int>(s2Length + 1));

	// lcs
	for (int i = 1; i <= s1Length; i++)
	{
		for (int j = 1; j <= s2Length; j++)
		{
			if (s1[i - 1] == s2[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	ret = dp[s1Length][s2Length];

	// ������
	int i = s1Length, j = s2Length;
	while (i > 0 && j > 0)
	{
		if (s1[i - 1] == s2[j - 1])	// �밢
		{
			answer += s1[i - 1];
			i--;
			j--;
		}
		else if (dp[i - 1][j] > dp[i][j - 1])	// ��
			i--;
		else // ��
			j--;
	}

	reverse(answer.begin(), answer.end());
}

int main()
{
	cin >> s1 >> s2;

	solution();

	cout << ret << '\n' << answer << '\n';
	return 0;
}