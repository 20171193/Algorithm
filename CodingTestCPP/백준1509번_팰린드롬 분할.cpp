// 백준 1509번 : 팰린드롬 분할
// DP + Manacher
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int INF = 2501;
bool isPD[INF][INF];
string str;

string ManacherFormat()
{
	string result = "#";
	for (char c : str)
	{
		result += c;
		result += '#';
	}
	return result;
}

vector<int> Manacher(const string& manStr)
{
	int len = (int)manStr.size();

	vector<int> rads(len, 0);
	int c = 0, r = 0;

	for (int i = 0; i < len; i++)
	{
		int opp = 2 * c - i;

		if (i < r)
			rads[i] = min(rads[opp], r - i);

		// 확장
		int lp = i - rads[i] - 1;
		int rp = i + rads[i] + 1;
		while (lp >= 0 && rp < len && manStr[lp--] == manStr[rp++])
			rads[i]++;

		if (i + rads[i] > r)
		{
			c = i;
			r = i + rads[i];
		}
	}

	return rads;
}

int solve()
{
	string manStr = ManacherFormat();
	vector<int> rads = Manacher(manStr);

	int manLen = manStr.size();
	for (int i = 0; i < manLen; i++)
	{
		int rad = rads[i];
		int l = i - rad;
		int r = i + rad;
		if (l < 0 || r >= manLen) continue;

		int s = (l + 1) / 2;
		int e = (r - 1) / 2;
		if (s <= e)
			isPD[s][e] = true;
	}

	int originLen = str.size();
	vector<int> dp(originLen + 1, INF);
	dp[0] = 0;
	for (int i = 1; i <= originLen; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (isPD[j][i - 1])
				dp[i] = min(dp[i], dp[j] + 1);
		}
	}

	return dp[originLen];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> str;

	cout << solve() << '\n';

	return 0;
}