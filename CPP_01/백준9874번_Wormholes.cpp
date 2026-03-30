// 백준 9874번 : Wormholes(https://www.acmicpc.net/problem/9874)
// 조건
// 1. 웜홀(2<=N<=12, 짝수) : 들어간 방향대로 나옴
// 2. 좌표는 x,y로 표현하고 항상 +x 방향으로 이동
//
// 풀이
// 1. 중복없는 짝짓기 (DFS)
// 2. 시뮬레이션 (벨만포드 방식)
#include <iostream>
#include <vector>
using namespace std;

int n, answer;
vector<pair<int, int>> hole;
vector<int> linkedHole, nearHole;

bool CheckCycle() {
	for (int start = 0; start < n; start++) {
		int cur = start;

		// 웜홀 개수만큼 시뮬레이션
		for (int i = 0; i < n; i++) {
			int next = linkedHole[cur];
			cur = nearHole[next];

			// 가까운 웜홀 없음 -> 탈출
			if (cur == -1) break;
		}
		// 탈출하지 못한경우 사이클
		if (cur != -1) return true;
	}
	return false;
}

// 웜홀 짝짓기
void dfs() {
	int left;
	for (left = 0; left < n; left++)
		if (linkedHole[left] == -1)
			break;

	if (left == n) {
		if (CheckCycle())
			answer++;
		return;
	}

	for (int right = left + 1; right < n; right++) {
		if (linkedHole[right] == -1) {
			linkedHole[left] = right;
			linkedHole[right] = left;
			dfs();
			// 초기화 
			linkedHole[left] = linkedHole[right] = -1;
		}
	}

}

void solution() {
	linkedHole.assign(n, -1);

	// 같은 y축에서 가장 가까이 위치한 웜홀
	nearHole.assign(n, -1);
	for (int i = 0; i < hole.size(); i++) {
		int minDist = 1000000001;
		int target = -1;
		for (int j = 0; j < hole.size(); j++) {
			if (i == j) continue;
			if (hole[i].second != hole[j].second) continue;

			int dist = hole[j].first - hole[i].first;
			if (dist >= 0 && dist < minDist) {
				minDist = dist;
				target = j;
			}
		}
		nearHole[i] = target;
	}

	dfs();
}

int main() {
	cin >> n;
	hole.assign(n, {});
	for (int i = 0; i < n; i++)
		cin >> hole[i].first >> hole[i].second;

	solution();
	cout << answer << '\n';
	return 0;
}