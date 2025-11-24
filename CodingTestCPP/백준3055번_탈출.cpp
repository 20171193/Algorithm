// 백준 3055번 : 탈출(https://www.acmicpc.net/problem/3055)
// BFS
#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

constexpr int MAX_DISTANCE = 2501;

int r, c;
int dx[4] = { 0,1,0,-1 }, dy[4] = { 1,0,-1,0 };
string arr[51];

void solution()
{
	string fail = "KAKTUS";

	// 물(*), 돌(X), 비버(D), 고슴(S), 빈곳(.)
	int answer = MAX_DISTANCE;
	queue<pair<int, int>> hogQ, waterQ;
	vector<vector<int>> water(r, vector<int>(c)), visited(r, vector<int>(c));

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (arr[i][j] == '*')
			{
				water[i][j] = 1;
				waterQ.push({ i,j });
			}
			else if (arr[i][j] == 'S')
			{
				visited[i][j] = 1;
				hogQ.push({ i,j });
			}
		}
	}

	// 물 확장
	while (!waterQ.empty())
	{
		auto cur = waterQ.front();
		waterQ.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = dy[i] + cur.first;
			int nx = dx[i] + cur.second;
			if (ny < 0 || ny >= r || nx < 0 || nx >= c) continue;
			if (arr[ny][nx] != '.' && arr[ny][nx] != 'S') continue;
			if (water[ny][nx]) continue;

			water[ny][nx] = water[cur.first][cur.second] + 1;
			waterQ.push({ ny,nx });
		}
	}
	// 고슴도치 이동
	while (!hogQ.empty())
	{
		auto cur = hogQ.front();
		hogQ.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = dy[i] + cur.first;
			int nx = dx[i] + cur.second;
			if (ny < 0 || ny >= r || nx < 0 || nx >= c)
				continue;
			if (arr[ny][nx] != '.' && arr[ny][nx] != 'D')
				continue;
			int nVisited = visited[cur.first][cur.second] + 1;
			// 조건 추가 : 물 확장이 더 빠른 경우
			if (visited[ny][nx]) continue;
			if (water[ny][nx] && water[ny][nx] <= nVisited) continue;

			visited[ny][nx] = nVisited;
			if (arr[ny][nx] == 'D')
				answer = min(answer, nVisited);

			hogQ.push({ ny,nx });
		}
	}

	if (answer == MAX_DISTANCE)
		cout << fail << '\n';
	else
		cout << answer - 1 << '\n';
}

int main()
{
	cin >> r >> c;
	for (int i = 0; i < r; i++)
		cin >> arr[i];

	solution();
	return 0;
}