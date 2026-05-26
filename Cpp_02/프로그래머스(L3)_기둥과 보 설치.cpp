// 프로그래머스(L3) : 기둥과 보 설치
// 조건
// 1. 기둥과 보
//  1-1. 기둥(세로)
//        : 바닥 위에 있거나 보의 한쪽 끝 부분 위에 있거나,
//          다른 기둥 위에 있어야 함(떠 있을 수 없음)
//  1-2. 보(가로)
//        : 한쪽 끝 부분이 기둥 위에 있거나,
//          또는 양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 함.
//  1-3. 입력대로 처리할 수 없으면 무시
// 2. 입력
//  2-1. n : build_frame.size
//  2-2. buildframe : [x,y,a,b]
//     x,y : 교차점 좌표
//     a : 0=기둥, 1=보
//     b : 0=삭제, 1=설치
// 3. 출력
//  3-1. 최종 구조물 상태 : [x,y,a]
//      : x,y,a 순 오름차
// 풀이
// 1. 그래프 형식 포맷
// 2. 시뮬레이션 : 설치/제거가 가능한지 확인
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

pair<int, int> IndexToPos(int size, int idx) {
	if (idx == 0) return { 0,0 };
	return { idx % size, idx / size };
}

int PosToIndex(int size, const pair<int, int>& pos) {
	return pos.first + pos.second * size;
}

// dir = {상,하,좌,우}
int PosToIndex(int size, const pair<int, int>& pos, int dir) {
	pair<int,int> tempPos = { pos.first + dx[dir], pos.second + dy[dir] };
	return PosToIndex(size, tempPos);
}

bool CanBuild(const pair<int,int>& p1, const pair<int,int>& p2, int i1, int i2, vector<unordered_set<int>>& graph, int type, int size) {
	// 기둥 : 하단에 기둥/보가 존재하는 경우만 가능
	if (type == 0) {
		if (p1.second == 0) return true;
		else if (graph[i1].find(PosToIndex(size, p1, 1)) != graph[i1].end()) return true;
		else if (graph[i1].find(PosToIndex(size, p1, 2)) != graph[i1].end()) return true;
		else if (graph[i1].find(PosToIndex(size, p1, 3)) != graph[i1].end()) return true;
	}
	// 보 : 양 끝 중 하나라도 기둥이 존재하거나 양 끝에 보가 존재하는 경우
	else if (type == 1) {
		if (graph[i1].find(PosToIndex(size, p1, 1)) != graph[i1].end()) return true;
		else if (graph[i2].find(PosToIndex(size, p2, 1)) != graph[i2].end()) return true;
		else if (graph[i1].find(PosToIndex(size, p1, 2)) != graph[i1].end()
			&& graph[i2].find(PosToIndex(size, p2, 3)) != graph[i2].end()) return true;
	}
	return false;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;

	int size = n + 1;
	vector<unordered_set<int>> graph(size*size);

	// [x,y,a,b]
	for (auto& frame : build_frame) {
		pair<int, int> p1 = make_pair(frame[0], frame[1]);
		pair<int, int> p2 = frame[2] == 0 ?
			make_pair(frame[0], frame[1] + 1) : make_pair(frame[0] + 1, frame[1]);

		int i1 = PosToIndex(size, p1), i2 = PosToIndex(size, p2);

		// 삭제
		if (frame[3] == 0) {
			graph[i1].erase(i2);
			graph[i2].erase(i1);
			// 모든 선분 검토
			bool canFlag = true;
			for (int s = 0; s < size * size; s++) {
				for (int e : graph[s]) {
					if (e < s) continue;

					auto sp = IndexToPos(size, s), ep = IndexToPos(size, e);
					if (!CanBuild(sp, ep, s, e, graph, e - s == 1, size)) {
						canFlag = false;
						break;
					}
				}

				if (!canFlag) break;
			}

			// 복구
			if (!canFlag) {
				graph[i1].insert(i2);
				graph[i2].insert(i1);
			}
		}
		// 설치
		else {
			if (CanBuild(p1, p2, i1, i2, graph, frame[2], size)){
				graph[i1].insert(i2);
				graph[i2].insert(i1);
			}
		}
	}

	for (int s = 0; s < size * size; s++) {
		for (int e : graph[s]) {
			if (e < s) continue;

			auto pos = IndexToPos(size, s);
			answer.push_back({ pos.first, pos.second, e - s == 1 ? 1 : 0 });
		}
	}

	// 정답 정렬
	sort(answer.begin(), answer.end(), [](const auto& a, const auto& b) {
		for (int i = 0; i < 3; i++) {
			if (a[i] != b[i])
				return a[i] < b[i];
		}
		return false;
		});
	return answer;
}
