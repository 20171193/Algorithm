// 백준 1600번 : 말이 되고픈 원숭이 
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;

constexpr int CHANGE_FLAG = 4;

// 0-3 : 원숭이, 4-11 : 말
int dx[12] = { 1,0,-1,0 ,-2,-1,1,2,-2,-1,1,2 };
int dy[12] = { 0,1,0,-1,1,2,2,1,-1,-2,-2,-1 };

int k, w, h, _map[201][201];

struct Pos {
	int _x, _y;
	Pos() : _x(0), _y(0) {}
	Pos(int x, int y) : _x(x), _y(y) {}
};

int bfs()
{
	vector<vector<vector<bool>>> visited(h + 1
		, vector<vector<bool>>(w + 1
			, vector<bool>(k + 1, 0)));

	// { y, x, horse move count}
	queue<tuple<int, int, int>> q;

	q.push({ 0,0,0 });
	visited[0][0][0] = true;

	int totalMoveCnt = 0;

	while (!q.empty())
	{
		int depth = q.size();
		while (depth--)
		{
			auto curNode = q.front();
			q.pop();

			int cy = get<0>(curNode)
				, cx = get<1>(curNode)
				, horseMoveCnt = get<2>(curNode);

			// 목적지 도착
			if (cy == h - 1 && cx == w - 1) return totalMoveCnt;

			for (int i = 0; i < 12; i++)
			{
				// 0-3 : 원숭이, 4-11 : 말
				int ny = dy[i] + cy;
				int nx = dx[i] + cx;
				int nHorseMoveCnt = horseMoveCnt;
				if (i >= CHANGE_FLAG)
				{
					if (horseMoveCnt >= k) break;
					nHorseMoveCnt += 1;
				}
				if (ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
				if (_map[ny][nx] == 1) continue;
				if (visited[ny][nx][nHorseMoveCnt]) continue;

				visited[ny][nx][nHorseMoveCnt] = true;
				q.push({ ny, nx, nHorseMoveCnt });
			}
		}
		// 한 뎁스 종료 후 moveCount 증가
		totalMoveCnt++;
	}

	return -1;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> k >> w >> h;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			cin >> _map[y][x];

	cout << bfs() << '\n';

	return 0;
}