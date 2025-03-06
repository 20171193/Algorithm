#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill)
{
	int answer = 0;

	// type(,공격, 회복), r1, c1, r2, c2, degree
	vector<vector<int>> skilled(board.size(), vector<int>(board[0].size()));
	for (const vector<int>& sk : skill)
	{
		int type = sk[0];
		int mnY = sk[1], mnX = sk[2];
		int mxY = sk[3], mxX = sk[4];
		int degree = type == 1 ? -sk[5] : sk[5];

		skilled[mnY][mnX] += degree;
		if (mxY < board.size() - 1)
			skilled[mxY + 1][mnX] -= degree;
		if (mxX < board[0].size() - 1)
			skilled[mnY][mxX + 1] -= degree;
		if (mxX < board[0].size() - 1 && mxY < board.size() - 1)
			skilled[mxY + 1][mxX + 1] += degree;
	}


	for (int i = 0; i < skilled.size(); i++)
		for (int j = 1; j < skilled[0].size(); j++)
			skilled[i][j] += skilled[i][j - 1];


	for (int j = 0; j < skilled[0].size(); j++)
		for (int i = 1; i < skilled.size(); i++)
			skilled[i][j] += skilled[i - 1][j];

	for (int i = 0; i < board.size(); i++)
		for (int j = 0; j < board[0].size(); j++)
			if (board[i][j] + skilled[i][j] > 0)
				answer++;

	return answer;
}
