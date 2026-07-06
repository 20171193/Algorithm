// 프로그래머스(L3) : 스타 수열
// 문제
// 1. 스타 수열 :수열 x에 대해
//  1-1. x의 길이가 2 이상의 짝수
//  1-2. x의 길이를 2n이라 할 때, 다음 n개의 집합
//      {x[0], x[1]}, {x[2], x[3]}, ..., {x[2n-2], x[2n - 1]}
//       의 교집합의 원소의 개수가 1이상
//  1-3. x[0] != x[1], x[2] != x[3], ... , x[2n-2] != x[2n -1]
// 2. 1차원 정수 배열 a가 주어질 때,
//    a에서 가장 긴 스타 수열의 길이를 return, 없다면 0을 return
// 조건
// 1. 1 <= a <= 500,000
// 2. 0 <= a[i] < a.size()
// 풀이
// 1. 교집합이 될 숫자별로 등장하는 인덱스 할당
// 2. 구간별 카운팅
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> a) {
	int n = a.size();
	int answer = 0;

	vector<vector<int>> poses(500001);
	for (int i = 0; i < n; i++) {
		poses[a[i]].push_back(i);
	}

	for (auto& pos : poses) {
		int k = pos.size();
		if (k < 2) continue;
		if (k * 2 <= answer) continue;

		// 앞 구간
		bool prevUsed = pos[0] > 0;
		int cnt = pos[0] > 0;

		// 내부 구간
		for (int i = 1; i < k; i++) {
			// 사이에 존재하는 원소 개수
			int gap = pos[i] - pos[i - 1] - 1;
			bool curUsed = false;
			// 원소가 2개 이상
			if (gap >= 2) {
				if (!prevUsed)	// 이전 원소 연결
					cnt++;
				cnt++;	// 현재 원소 연결
				curUsed = true;
			}
			// 왼쪽 연결
			else if (gap == 1) {
				if (!prevUsed) {	// 이전 원소 연결
					cnt++;
					curUsed = false;
				}
				else {	// 현재 원소 연결
					cnt++;
					curUsed = true;
				}
			}
			prevUsed = curUsed;
		}

		if (!prevUsed && pos[k - 1] < n - 1) cnt++;

		answer = max(answer, cnt * 2);
	}

	return answer;
}
