// 백준 1786번 : 찾기
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string T, P;

// 패턴 내 반복되는 문자열 인덱스
vector<int> GetPrefixIndex()
{
	int size = P.size();
	vector<int> pi(size);

	int j = 0;
	for (int i = 1; i < size; i++)
	{
		while (j > 0 && P[i] != P[j])
			j = pi[j - 1];

		if (P[i] == P[j])
			pi[i] = ++j;
	}
	return pi;
}

// KMP풀이
vector<int> solution()
{
	vector<int> result;

	// p 문자열 prefix index 할당
	vector<int> pi = GetPrefixIndex();

	int tSize = T.size();
	int pSize = P.size();

	int j = 0;
	for (int i = 0; i < tSize; i++)
	{
		while (j > 0 && T[i] != P[j])
			j = pi[j - 1];

		if (T[i] == P[j])
		{
			if (j == pSize - 1)
			{
				result.push_back(i - pSize + 2);	// 1-based
				j = pi[j];
			}
			else
				j++;
		}
	}

	return result;
}

int main()
{
	getline(cin, T);
	getline(cin, P);

	vector<int> answer = solution();
	cout << answer.size() << '\n';
	for (int ans : answer)
		cout << ans << '\n';
	return 0;
}