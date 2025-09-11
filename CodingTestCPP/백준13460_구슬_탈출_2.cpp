// 백준 13460번 : 구슬 탈출 2
#include <iostream>
#include <queue>
using namespace std;

int n, m;
char board[11][11];
int visited[101][101];
pair<int, int> red, blue, hole;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0, 1,-1 };

struct State {
	pair<int, int> _rPos, _bPos;
	int _count = 0;
	State(pair<int, int> rPos, pair<int, int> bPos, int count) : _rPos(rPos), _bPos(bPos), _count(count) {}
};

pair<int, int> Move(pair<int, int> pos, int dir)
{
	int ny = pos.first + dy[dir];
	int nx = pos.second + dx[dir];

	while (board[ny][nx] != '#' && board[ny][nx] != 'O')
	{
		ny += dy[dir];
		nx += dx[dir];
	}

	if (board[ny][nx] == 'O')
		return { ny,nx };
	else
		return { ny - dy[dir], nx - dx[dir] };
}

// 축 확인 후 먼저 이동할 구슬좌표 반환
pair<int, int> GetMoveOrder(pair<int, int> rPos, pair<int, int> bPos, int dir)
{
	// 축이 다른 경우
	if ((dir < 2 && rPos.first != bPos.first)
		|| (dir >= 2 && rPos.second != bPos.second))
		return rPos;

	// 같은 축
	if ((dir == 0 && bPos.second > rPos.second)
		|| (dir == 1 && bPos.second < rPos.second)
		|| (dir == 2 && bPos.first > rPos.first)
		|| (dir == 3 && bPos.first < rPos.first))
		return bPos;

	return rPos;
}

int solution()
{
	int result = 12;
	int holeGrid = hole.first * m + hole.second;
	int rGrid = red.first * m + red.second;
	int bGrid = blue.first * m + blue.second;

	// 최초 위치도 카운팅
	queue<State> q;
	q.push({ red, blue, 1 });
	visited[rGrid][bGrid] = 1;

	while (!q.empty())
	{
		State cur = q.front();
		q.pop();

		if (cur._count >= 10) continue;

		for (int i = 0; i < 4; i++)
		{
			pair<int, int> nrPos, nbPos;
			if (GetMoveOrder(cur._rPos, cur._bPos, i) == cur._rPos)
			{
				nrPos = Move(cur._rPos, i);
				nbPos = Move(cur._bPos, i);
				if (board[nbPos.first][nbPos.second] == 'O') continue;
				// 겹침 처리
				if (nbPos == nrPos)
					nbPos = { nbPos.first - dy[i], nbPos.second - dx[i] };
			}
			else
			{
				nbPos = Move(cur._bPos, i);
				if (board[nbPos.first][nbPos.second] == 'O') continue;
				nrPos = Move(cur._rPos, i);
				// 겹침 처리
				if (nbPos == nrPos)
					nrPos = { nrPos.first - dy[i], nrPos.second - dx[i] };
			}

			if (nrPos == cur._rPos && nbPos == cur._bPos)
				continue;

			rGrid = nrPos.first * m + nrPos.second;
			bGrid = nbPos.first * m + nbPos.second;
			if (visited[rGrid][bGrid] && visited[rGrid][bGrid] <= cur._count + 1)
				continue;

			visited[rGrid][bGrid] = cur._count + 1;
			if (rGrid == holeGrid)
				result = min(result, cur._count + 1);
			q.push({ nrPos, nbPos, cur._count + 1 });
		}
	}

	if (result > 11)
		return -1;
	else
		return result - 1;
}

int main()
{
	cin >> n >> m;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cin >> board[y][x];

			if (board[y][x] == 'R') red = make_pair(y, x);
			else if (board[y][x] == 'B') blue = make_pair(y, x);
			else if (board[y][x] == 'O') hole = make_pair(y, x);
		}
	}

	cout << solution() << '\n';
	return 0;
}