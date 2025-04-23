// 백준 12850번 : 본대 산책2
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;
int d;

vector<vector<ll>> operator*(const vector<vector<ll>>& matrix1, const vector<vector<ll>>& matrix2)
{
	int size = matrix1.size();
	vector<vector<ll>> ret(size, vector<ll>(size));

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
				ret[i][j] = (ret[i][j] + (matrix1[i][k] * matrix2[k][j]) % MOD) % MOD;

	return ret;
}

struct Matrix
{
	int _size;
	vector<vector<ll>> _matrix;

	Matrix(int size)
	{
		_size = size;
		_matrix.assign(_size, vector<ll>(_size, 0));
	}

	void AddEdge(int s, int e)
	{
		_matrix[s][e] = 1;
		_matrix[e][s] = 1;
	}

	vector<vector<ll>> Pow(vector<vector<ll>> matrix, int n)
	{
		if (n == 1)
			return matrix;

		vector<vector<ll>> half = Pow(matrix, n / 2);
		vector<vector<ll>> squared = half * half;

		if (n % 2 == 0)
			return squared;
		else  // n % 2 == 1
			return squared * matrix;
	}
};

int main()
{
	cin >> d;

	Matrix matrix(8);
	matrix.AddEdge(0, 1);	// 정보-전산
	matrix.AddEdge(0, 2);	// 정보-미래
	matrix.AddEdge(1, 2);	// 전산-미래
	matrix.AddEdge(1, 3);	// 전산-신양
	matrix.AddEdge(2, 3);	// 미래-신양
	matrix.AddEdge(2, 4);	// 미래-한경직기념
	matrix.AddEdge(3, 4);	// 신양-한경직기념
	matrix.AddEdge(3, 5);	// 신양-진리
	matrix.AddEdge(4, 5);	// 한경직기념-진리
	matrix.AddEdge(4, 6);	// 한경직기념-형남
	matrix.AddEdge(5, 7);	// 진리-학생회
	matrix.AddEdge(6, 7);	// 형남-학생회

	vector<vector<ll>> result = matrix.Pow(matrix._matrix, d);
	cout << result[0][0] << '\n';

	return 0;
}