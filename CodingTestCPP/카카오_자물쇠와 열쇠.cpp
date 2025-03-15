#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> Rotate(int size, const vector<vector<int>>& src)
{
	vector<vector<int>> result(size, vector<int>(size));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			result[i][j] = src[size - j - 1][i];
		}
	}

	return result;
}

bool Check(int sx, int sy, int count, const vector<vector<int>>& key, const vector<vector<int>>& lock)
{
	for (int y = max(0, sy); y < min(sy + key.size(), lock.size()); y++)
	{
		for (int x = max(0, sx); x < min(sx + key.size(), lock.size()); x++)
		{
			if (lock[y][x] == key[y - sy][x - sx])
				return false;
			if (key[y - sy][x - sx] == 1)
				count--;
		}
	}
	return count == 0;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	bool answer = true;
	int m = key.size();
	int n = lock.size();
	vector<vector<int>> keys[4]{ key };
	for (int i = 1; i < 4; i++)
		keys[i] = Rotate(m, keys[i - 1]);

	int count = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (lock[i][j] == 0)
				count++;

	if (count == 0)
		return true;

	for (int i = -(m - 1); i < n; i++)
	{
		for (int j = -(m - 1); j < n; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (Check(i, j, count, keys[k], lock))
					return true;
			}
		}
	}

	return false;
}