// 백준 2239번 : 스도쿠
#include <iostream>
#include <vector>
using namespace std;

// 행, 열, 3*3 박스 비트마스킹
int col[9], row[9], box[9];
string inputs[9];
vector<pair<int, int>> zeros;

bool dfs(int depth)
{
	if (depth == zeros.size())
	{
		for (const string& str : inputs)
			cout << str << '\n';
		return true;
	}

	int r = zeros[depth].first;
	int c = zeros[depth].second;
	int b = r / 3 * 3 + c / 3;

	for (int i = 1; i <= 9; i++)
	{
		int bit = 1 << i;
		if (row[r] & bit || col[c] & bit || box[b] & bit) continue;

		inputs[r][c] = i + '0';
		row[r] |= bit;
		col[c] |= bit;
		box[r / 3 * 3 + c / 3] |= bit;

		if (dfs(depth + 1))
			return true;

		inputs[r][c] = '0';
		row[r] ^= bit;
		col[c] ^= bit;
		box[r / 3 * 3 + c / 3] ^= bit;
	}
	return false;
}

int main()
{
	for (int i = 0; i < 9; i++)
		cin >> inputs[i];


	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			if (inputs[r][c] == '0')
			{
				zeros.push_back({ r,c });
				continue;
			}

			int bit = 1 << (inputs[r][c] - '0');

			col[c] |= bit;
			row[r] |= bit;
			box[r / 3 * 3 + c / 3] |= bit;
		}
	}

	dfs(0);

	return 0;
}