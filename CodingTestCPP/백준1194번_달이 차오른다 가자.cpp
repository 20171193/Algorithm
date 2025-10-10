// 백준 1194번 : 달이 차오른다, 가자.
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>
using namespace std;

constexpr int ASCII_A = 65;
constexpr int ASCII_a = 97;

// a-f : 열쇠 (97-102)
// A-F : 문 (65-70)
// 0 : 현위치
// 1 : 출구
// # : 벽
// . : 빈칸

// 50*50*33
// 80000

int solution(int n, int m, const pair<int, int>& start, const vector<vector<char>>& grid)
{
	int retCount = INT_MAX;

	// bfs+비트마스킹
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	// y, x, 열쇠bit
	queue<tuple<int, int, int>> q;

	vector<vector<vector<int>>> visited(n
		, vector<vector<int>>(m
			, vector<int>(1 << 6)));

	q.push(make_tuple(start.first, start.second, 0));
	visited[start.first][start.second][0] = 1;

	while (!q.empty())
	{
		auto cur = q.front();
		q.pop();

		int curY = get<0>(cur);
		int curX = get<1>(cur);
		int curBit = get<2>(cur);

		if (retCount <= visited[curY][curX][curBit]) continue;

		for (int i = 0; i < 4; i++)
		{
			int nextY = curY + dy[i];
			int nextX = curX + dx[i];
			int nextBit = curBit;
			if (nextY < 0 || nextY >= n || nextX < 0 || nextX >= m) continue;
			if (grid[nextY][nextX] == '#') continue;

			char nextNode = grid[nextY][nextX];

			if (nextNode >= 'A' && nextNode <= 'F')
			{
				int doorBit = 1 << ((int)nextNode - ASCII_A);
				// 열쇠가 없는 경우
				if ((doorBit & curBit) == 0)
					continue;
			}
			else if (nextNode >= 'a' && nextNode <= 'f')
			{
				int keyBit = 1 << ((int)nextNode - ASCII_a);
				// 열쇠 획득
				if ((keyBit & curBit) == 0)
					nextBit |= keyBit;
			}

			if (visited[nextY][nextX][nextBit] == 0 || visited[nextY][nextX][nextBit] > visited[curY][curX][curBit] + 1)
				visited[nextY][nextX][nextBit] = visited[curY][curX][curBit] + 1;
			else
				continue;

			if (nextNode == '1')
			{
				if (retCount > visited[nextY][nextX][nextBit])
					retCount = visited[nextY][nextX][nextBit];
				continue;
			}

			q.push(make_tuple(nextY, nextX, nextBit));
		}
	}

	if (retCount == INT_MAX)
		return -1;
	return retCount - 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 0, m = 0;
	cin >> n >> m;

	vector<vector<char>> grid(n, vector<char>(m));
	pair<int, int> start;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> grid[i][j];
			if (grid[i][j] == '0')
				start = { i,j };
		}
	}

	cout << solution(n, m, start, grid) << '\n';
	return 0;
}