// ���� 1799�� : ���
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n, blackRet, whiteRet;
// �ð��ʰ� -> ü���� ����(��,��)
//          -> Ž�������� ����
vector<pair<int, int>> blacks, whites;
vector<vector<int>> chess;

// x+y, x-y �밢
bool diagSum[19], diagDiff[19];

void dfs(int depth, int count, bool isWhite)
{
	auto& cells = isWhite ? whites : blacks;
	int& ret = isWhite ? whiteRet : blackRet;

	ret = max(ret, count);

	if (depth == cells.size() || cells.size() - depth + count <= ret)
		return;

	for (int i = depth; i < cells.size(); i++)
	{
		// x+y ���� �밢��
		int sum = cells[i].first + cells[i].second;
		// x-y ��� �밢��
		int diff = cells[i].first - cells[i].second + n - 1;

		if (!diagSum[sum] && !diagDiff[diff])
		{
			diagSum[sum] = diagDiff[diff] = true;
			dfs(i + 1, count + 1, isWhite);
			diagSum[sum] = diagDiff[diff] = false;
		}
	}
}

int main()
{
	cin >> n;
	chess.assign(n, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> chess[i][j];
			if (chess[i][j] == 1)
			{
				if ((i + j) % 2 == 0)
					whites.push_back({ i,j });
				else
					blacks.push_back({ i,j });
			}
		}
	}

	dfs(0, 0, true);
	dfs(0, 0, false);

	cout << blackRet + whiteRet << '\n';

	return 0;
}