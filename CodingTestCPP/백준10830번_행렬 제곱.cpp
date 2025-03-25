// 백준 10830번 행렬 제곱
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int MOD = 1000;

vector<vector<int>> MatrixMultiply(const vector<vector<int>>& a, const vector<vector<int>>& b)
{
	int aRowSize = a.size();
	int aColSize = a[0].size();
	int bRowSize = b.size();
	int bColSize = b[0].size();

	if (aColSize != bRowSize)
		return {};

	vector<vector<int>> resultMatrix(aRowSize, vector<int>(bColSize));

	for (int row = 0; row < aRowSize; row++)
		for (int col = 0; col < bColSize; col++)
			for (int com = 0; com < aColSize; com++)
				resultMatrix[row][col] = (resultMatrix[row][col] + a[row][com] * b[com][col]) % MOD;

	return resultMatrix;
}

vector<vector<int>> MatrixPower(vector<vector<int>>& matrix, ll exp)
{
	if (matrix.size() != matrix[0].size())
		return {};
	int size = matrix.size();
	vector<vector<int>> resultMatrix(size, vector<int>(size, 0));
	// 단위행렬
	for (int i = 0; i < size; i++)
		resultMatrix[i][i] = 1;

	while (exp > 0)
	{
		// 홀수 처리
		if (exp % 2 == 1)
			resultMatrix = MatrixMultiply(resultMatrix, matrix);
		// 분할정복 : matrix^(exp/2) * matrix^(exp/2)
		matrix = MatrixMultiply(matrix, matrix);

		exp /= 2;
	}

	return resultMatrix;
}

int main()
{
	int n;
	ll b;

	cin >> n >> b;
	vector<vector<int>> matrix(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> matrix[i][j];

	vector<vector<int>> answer = MatrixPower(matrix, b);
	for (int i = 0; i < answer.size(); i++)
	{
		for (int j = 0; j < answer[0].size(); j++)
		{
			cout << answer[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}