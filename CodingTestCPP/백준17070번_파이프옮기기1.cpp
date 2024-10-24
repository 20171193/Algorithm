// 백준 17070번 파이프 옮기기 1
#include <iostream>
#include <queue>
using namespace std;

int n, arr[17][17];
int visited[17][17][3];

int dx[3] = { 1,0,1 };
int dy[3] = { 0,1,1 };

// <shape, dist>
// 가로 : 0 - 0,2
// 세로 : 1 - 1,2
// 대각 : 2 - 0,1,2
struct pipe {
	int x;
	int y;
	int shape;
	pipe(int _y, int _x, int _shape)
	{
		x = _x;
		y = _y;
		shape = _shape;
	}
	vector<pipe> LinkedPipe()
	{
		if (shape == 0)
			return { pipe(y + dy[0], x + dx[0], 0), pipe(y + dy[2], x + dx[2], 2) };
		else if (shape == 1)
			return { pipe(y + dy[1], x + dx[1], 1), pipe(y + dy[2], x + dx[2], 2) };
		else
			return { pipe(y + dy[0], x + dx[0], 0),pipe(y + dy[1], x + dx[1], 1), pipe(y + dy[2], x + dx[2], 2) };
	}
};

bool CheckBound(pipe p)
{
	if (p.x > n || p.x < 1 || p.y > n || p.y < 1)
		return false;
	if (arr[p.y][p.x])
		return false;
	return true;
}

int ShapeCount(pipe prev, pipe cur)
{
	// 대각 가로
	if (cur.shape == 0)
		return visited[prev.y][prev.x][0] + visited[prev.y][prev.x][2];
	// 대각 세로
	else if (cur.shape == 1)
		return visited[prev.y][prev.x][1] + visited[prev.y][prev.x][2];
	// 가로 세로 대각
	else
		return visited[prev.y][prev.x][0] + visited[prev.y][prev.x][1] + visited[prev.y][prev.x][2];
}

void bfs()
{
	queue<pipe> q;
	q.push(pipe(1, 2, 0));
	visited[1][2][0] = 1;

	while (q.size() > 0)
	{
		pipe cur = q.front();
		q.pop();

		vector<pipe> nexts = cur.LinkedPipe();
		for (int i = 0; i < nexts.size(); i++)
		{
			if (!CheckBound(nexts[i])) continue;
			int ny = nexts[i].y;
			int nx = nexts[i].x;
			int nShape = nexts[i].shape;

			if (visited[ny][nx][nShape])
			{
				visited[ny][nx][nShape] += ShapeCount(cur, nexts[i]);
				cout << "(" << ny << "," << nx << ")" << nShape << visited[ny][nx][nShape] << '\n';
				continue;
			}
			visited[ny][nx][nShape] += ShapeCount(cur, nexts[i]);
			cout << "(" << ny << "," << nx << ")" << nShape << visited[ny][nx][nShape] << '\n';
			q.push(nexts[i]);
		}
	}
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> arr[i][j];
		}
	}
	visited[1][2][0] = 1;
	bfs();
	cout << visited[n][n][0] + visited[n][n][1] + visited[n][n][2];
	return 0;
}