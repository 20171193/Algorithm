// 백준 3860번 : 할로윈 묘지(https://www.acmicpc.net/problem/3860)
// 조건
// 1. h(1<=30) * w(1<=30)
// 2. 귀신구멍 시간t(-10,000<=t<=10,000)
//
// 풀이
// 1. 경로 상에 음수사이클이 존재할 경우 확인 (벨만-포드)
// 2. 경로 설정
//  2-1. 각 노드 별로 4방향 간선 할당 h*w*4 
//  2-2. 벨만-포드
// 
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;
typedef long long ll;
enum MapInfo {
	TOMB = -1,
	GRASS = 0,
	HOLE = 1
};

int w, h, g, x, y, e, arr[31][31], visited[31][31];
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
pair<int, int> hole[901];

int PosToIndex(pair<int, int> pos)
{
	return pos.first * w + pos.second;
}
pair<int, int> IndexToPos(int index)
{
	return { index / w, index % w };
}

struct Edge {
	int from, to, cost;
	Edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

vector<Edge> MakeEdges() {
	vector<Edge> edges;

	for (int r = 0; r < h; r++) {
		for (int c = 0; c < w; c++) {
			// 묘비, 도착 지점 제외
			if (arr[r][c] == TOMB || (r == h - 1 && c == w - 1)) continue;

			int curIndex = PosToIndex({ r,c });
			// 귀신 구멍
			if (arr[r][c] == HOLE) {
				// 간선 할당
				edges.push_back({ curIndex, hole[curIndex].first, hole[curIndex].second });
				continue;
			}

			for (int d = 0; d < 4; d++) {
				int nr = r + dy[d];
				int nc = c + dx[d];

				if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
				// 묘비 제외
				if (arr[nr][nc] == TOMB) continue;
				// 간선 할당
				edges.push_back({ curIndex, PosToIndex({ nr, nc }), 1 });
			}
		}

	}

	return edges;
}

string solution() {
	int nodeCount = h * w;
	vector<Edge> edges = MakeEdges();

	vector<ll> dist(nodeCount, LLONG_MAX);

	// 벨만-포드 수행
	dist[0] = 0;
	for (int i = 0; i < nodeCount; i++) {
		for (int j = 0; j < edges.size(); j++) {
			int from = edges[j].from;
			int to = edges[j].to;
			int cost = edges[j].cost;

			if (dist[from] != LLONG_MAX && dist[to] > dist[from] + cost)
			{
				dist[to] = dist[from] + cost;

				// 마지막 라운드 갱신 확인
				if (i == nodeCount - 1)
					return "Never";
			}
		}
	}


	if (dist[nodeCount - 1] == LLONG_MAX)
		return "Impossible";
	else
		return to_string(dist[nodeCount - 1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	vector<string> answer;

	while (true) {
		cin >> w >> h;
		if (w == 0 || h == 0) break;

		// 묘비 입력
		cin >> g;
		for (int i = 0; i < g; i++) {
			cin >> x >> y;
			arr[y][x] = TOMB;
		}

		// 귀신 구멍 입력
		cin >> e;
		for (int i = 0; i < e; i++) {
			int x1, y1, x2, y2, t;
			cin >> x1 >> y1 >> x2 >> y2 >> t;

			arr[y1][x1] = HOLE;
			hole[PosToIndex({ y1, x1 })] = { PosToIndex({y2, x2}), t };
		}

		answer.push_back(solution());
		memset(arr, 0, sizeof(arr));
		memset(hole, 0, sizeof(hole));
	}

	for (const string& ans : answer)
		cout << ans << '\n';

	return 0;
}