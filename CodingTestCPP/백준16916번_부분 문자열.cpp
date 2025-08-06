// 백준 16916번 : 부분 문자열
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string S, P;

vector<int> GetPrefixIndex()
{
	int strSize = P.size();
	vector<int> pi(strSize);

	int j = 0;
	for (int i = 1; i < pi.size(); i++)
	{
		while (j > 0 && P[i] != P[j])
			j = pi[j - 1];

		if (P[i] == P[j])
			pi[i] = ++j;
	}

	return pi;
}

int solution()
{
	vector<int> pi = GetPrefixIndex();

	int sSize = S.size();
	int pSize = P.size();

	int pIdx = 0;
	for (int sIdx = 0; sIdx < S.size(); sIdx++)
	{
		while (pIdx > 0 && S[sIdx] != P[pIdx])
			pIdx = pi[pIdx - 1];

		if (S[sIdx] == P[pIdx])
		{
			if (pIdx == pSize - 1)
				return 1;
			else
				pIdx++;
		}
	}
}

int main()
{
	getline(cin, S);
	getline(cin, P);

	cout << solution() << '\n';
	return 0;
}