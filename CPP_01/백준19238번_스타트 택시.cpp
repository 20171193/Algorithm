// 백준 19238번 : 스타트 택시(https://www.acmicpc.net/problem/19238)
// 조건 
// 1. 맵 n*n(n<=20), 상하좌우 이동 (이동 시 연료 1 소모)
//  1-1. 벽(1)과, 빈칸(0) 존재
// 2. 손님 m(n^2), 현재 위치에서 가장 가까운 승객 우선 > 행 번호 우선 
// 3. 한 승객을 목적지로 이동 시키면 소모한 연료 양의 두 배가 충전
// 4. 이동 중 연료가 바닥나면 이동 실패, 업무 종료
// 5. 모든 손님을 이동시키고 남은 연료의 양 출력 (실패 시 -1 출력)
//
// 풀이
// 1. 맵에 고객번호 마킹 (2~m)
// 2. a* (고객-목적지까지 최단 경로)
// 3. bfs (현 위치에서 가장 가까운 고객 찾기(arr[y][x] >= 2))
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <algorithm>
using namespace std;

int n, m, fuel, py, px, arr[21][21], visited[21][21], clientIndex[401], clientCost[403];
pair<int, int> clientPos[403], destPos[403];

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

#pragma region Astar(고객-목적지 최단거리 찾기)
struct AstarNode {
	int y, x, g, f;
	AstarNode(int y, int x, int g, int h) : y(y), x(x), g(g), f(this->g + h) {}
	bool operator<(const AstarNode& other) const {
		return f > other.f;
	}
};
int GetManhattan(int sy, int sx, int ty, int tx) { return abs(ty - sy) + abs(tx - sx); }
int astar(int sy, int sx, int ty, int tx) {
	priority_queue<AstarNode> pq;
	pq.push({ sy, sx, 0, GetManhattan(sy,sx, ty,tx) });
	visited[sy][sx] = 0;

	while (!pq.empty()) {
		auto cur = pq.top(); pq.pop();

		if (cur.g > visited[cur.y][cur.x])
			continue;
		if (cur.y == ty && cur.x == tx)
			return cur.g;

		for (int d = 0; d < 4; d++) {
			int ny = cur.y + dy[d];
			int nx = cur.x + dx[d];
			if (ny < 1 || ny > n || nx < 1 || nx > n) continue;
			if (arr[ny][nx] == 1) continue;

			int ng = cur.g + 1;
			if (visited[ny][nx] <= ng) continue;

			pq.push({ ny,nx, ng, GetManhattan(ny,nx, ty,tx) });
			visited[ny][nx] = ng;
		}
	}

	return -1;
}
#pragma endregion

#pragma region BFS(가장 가까운 고객 찾기)
struct Client {
	int y, x, dist, index;
	Client(int y, int x, int dist, int index) : y(y), x(x), dist(dist), index(index) {}
	bool operator<(const Client& other) const {
		if (dist == other.dist) {
			if (y == other.y)
				return x > other.x;
			return y > other.y;
		}
		return dist > other.dist;
	}
};
Client bfs(int cy, int cx) {
	if (arr[cy][cx] >= 2) return { cy, cx, 0 ,arr[cy][cx] };

	// 찾은 고객 할당
	priority_queue<Client> clients;

	queue<pair<int, int>> q;
	visited[cy][cx] = 0;
	q.push({ cy, cx });

	while (!q.empty()) {
		auto cur = q.front(); q.pop();

		if (!clients.empty()
			&& visited[cur.first][cur.second] >= clients.top().dist) continue;

		for (int d = 0; d < 4; d++) {
			int ny = cur.first + dy[d];
			int nx = cur.second + dx[d];
			if (ny < 1 || ny > n || nx < 1 || nx > n) continue;
			if (visited[ny][nx] || (ny == cy && nx == cx)) continue;

			if (arr[ny][nx] == 1)
				continue;
			else if (arr[ny][nx] >= 2) // 시작 지점을 1로 방문했기에 현 위치 거리 할당
			{
				visited[ny][nx] = visited[cur.first][cur.second] + 1;
				clients.push({ ny,nx, visited[ny][nx], arr[ny][nx] });
				continue;
			}

			q.push({ ny,nx });
			visited[ny][nx] = visited[cur.first][cur.second] + 1;
		}
	}

	if (clients.empty())
		return { -1,-1,-1,-1 };
	else
		return clients.top();
}

int solution() {
	// 고객-목적지 최단거리 할당 (Astar)
	for (int i = 2; i < m + 2; i++) {
		fill(&visited[0][0], &visited[0][0] + 21 * 21, 401);
		clientCost[i] = astar(clientPos[i].first, clientPos[i].second, destPos[i].first, destPos[i].second);
		// 고객이 목적지에 도달할 수 없는 경우
		if (clientCost[i] == -1)
			return -1;
	}

	memset(visited, 0, sizeof(visited));

	// 택시 시뮬레이션
	int clearCount = 0;
	int curFuel = fuel, cy = py, cx = px;

	while (true) {
		auto client = bfs(cy, cx);
		int cIndex = client.index;
		int cDist = client.dist;
		// 가까운 고객 존재 여부
		if (cIndex == -1) return -1;
		// 운행 가능 여부
		if (curFuel < cDist + clientCost[cIndex]) return -1;

		// 맵에서 완료한 고객 마킹
		arr[clientPos[cIndex].first][clientPos[cIndex].second] = 0;
		clearCount++;

		// 고객까지 이동한 거리만큼 연료소모
		// *운행 완료 시 clientCost[cIndex] * 2 만큼 연료 보충(뺄 필요 없음)
		curFuel -= cDist;
		// 연료 채우기 (운행 거리만큼 보충)
		curFuel += clientCost[cIndex];
		if (clearCount == m) return curFuel;

		// 택시 위치 변경
		cy = destPos[cIndex].first;
		cx = destPos[cIndex].second;

		memset(visited, 0, sizeof(visited));
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> fuel;
	// 1-based input
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> arr[i][j];

	cin >> py >> px;
	for (int idx = 2; idx < m + 2; idx++) {
		int cy, cx, ty, tx;
		cin >> cy >> cx >> ty >> tx;

		// 그래프 할당
		arr[cy][cx] = idx;
		int cIdx = cy * n + cx;
		int tIdx = ty * n + tx;
		// 고객 인덱스 매핑
		clientIndex[cIdx] = idx;
		clientPos[idx] = { cy, cx };
		destPos[idx] = { ty, tx };
	}

	cout << solution() << '\n';
	return 0;
}