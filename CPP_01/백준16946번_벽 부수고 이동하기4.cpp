// 백준 16946번 : 벽 부수고 이동하기 4
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

int n, m, grid[1001][1001], answer[1001][1001], mark;
// 영역 번호, 영역 넓이 
pair<int, int> area[1001][1001];
bool visited[1001][1001];

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

// bfs
void GetArea(int y, int x)
{
	queue<pair<int, int>> neighbor, path;

	neighbor.push({ y,x });
	path.push({ y,x });
	visited[y][x] = true;

	while (!neighbor.empty())
	{
		int cx = neighbor.front().second;
		int cy = neighbor.front().first;
		neighbor.pop();

		for (int d = 0; d < 4; d++)
		{
			int nx = dx[d] + cx;
			int ny = dy[d] + cy;
			if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
			if (grid[ny][nx] == 1) continue;
			if (visited[ny][nx]) continue;

			visited[ny][nx] = true;
			neighbor.push({ ny, nx });
			path.push({ ny, nx });
		}
	}

	int count = path.size();
	while (!path.empty())
	{
		area[path.front().first][path.front().second] = { mark, count };
		path.pop();
	}
	mark++;
}

void solve()
{
	// 빈 영역 넓이할당
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (grid[y][x] == 1) continue;
			if (visited[y][x]) continue;

			GetArea(y, x);
		}
	}

	unordered_set<int> marked;
	// 인접 영역 넓이합
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (grid[y][x] == 0) continue;

			// 현재 위치포함
			int sum = 1;
			for (int d = 0; d < 4; d++)
			{
				int nx = dx[d] + x;
				int ny = dy[d] + y;

				if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
				if (grid[ny][nx] == 1) continue;
				// 이미 확인한 영역인지
				if (marked.find(area[ny][nx].first) != marked.end()) continue;

				sum += area[ny][nx].second;
				marked.insert(area[ny][nx].first);
			}

			answer[y][x] = sum % 10;
			marked.clear();
		}
	}
}

int main()
{
	cin >> n >> m;
	for (int y = 0; y < n; y++)
	{
		string temp;
		cin >> temp;
		for (int x = 0; x < m; x++)
			grid[y][x] = temp[x] == '0' ? 0 : 1;
	}

	solve();

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cout << answer[y][x];
		}
		cout << '\n';
	}

	return 0;
}