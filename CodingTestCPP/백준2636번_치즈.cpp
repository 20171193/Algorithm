// 백준 2636번 : 치즈 (https://www.acmicpc.net/problem/2636)
// 1. 맵의 가장 자리는 항상 0
// 2. 가장 자리부터 BFS
// 추가 : 슬라이딩 윈도우 (치즈 발견 시, 현 위치와 치즈 위치 방문체크 후 원복)
//      : 입력이 클 경우 고려
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, arr[101][101];
int dx[4] = { 1,0,-1,0 }
, dy[4] = { 0,1,0,-1 };

pair<int, int> solution()
{
	vector<vector<bool>> visited(n, vector<bool>(m));
	queue<pair<int, int>> q, melt;
	bool flag = true;
	int prevCount = 0, time = 0;

	while (flag)
	{
		visited[0][0] = true;
		q.push({ 0,0 });
		// BFS 녹는 치즈 수집
		while (!q.empty())
		{
			auto cur = q.front();
			q.pop();

			for (int i = 0; i < 4; i++)
			{
				int ny = dy[i] + cur.first
					, nx = dx[i] + cur.second;

				if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
				if (visited[ny][nx]) continue;

				visited[ny][nx] = true;

				if (arr[ny][nx] == 1)
					melt.push({ ny,nx });
				else
					q.push({ ny,nx });
			}
		}

		if (melt.empty())
		{
			flag = false;
			break;
		}

		// 치즈 녹이기 
		prevCount = melt.size();
		time++;
		while (!melt.empty())
		{
			arr[melt.front().first][melt.front().second] = 0;
			melt.pop();
		}

		// 방문 배열 원복
		for (int i = 0; i < n; i++)
			fill(visited[i].begin(), visited[i].end(), false);
	}

	return { time, prevCount };
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> arr[i][j];

	auto p = solution();
	cout << p.first << '\n' << p.second << '\n';
	return 0;
}