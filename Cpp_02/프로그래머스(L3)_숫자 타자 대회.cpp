// 프로그래머스(L3) : 숫자 타자 대회
// 문제
// 1. 숫자 자판(0~9)을 왼손/오른손 엄지손가락 두 개로만 입력.
//    왼손은 4에서, 오른손은 6에서 시작.
// 2. 숫자 하나를 입력할 때 드는 가중치
//    - 같은 자리(직전 위치와 동일) 다시 누름 : 1
//    - 상하좌우로 인접한 칸 이동 후 누름 : 2
//    - 대각선으로 인접한 칸 이동 후 누름 : 3
//    - 그 외(비인접) : 위 가중치들로 이동 가능한 "최단 경로 합"
// 3. 특정 숫자 칸 위에는 동시에 두 손가락이 있을 수 없음
//    → 이미 그 숫자 위에 있는 손가락으로만 그 숫자를 입력 가능
// 4. numbers 문자열을 순서대로 모두 입력하는 데 필요한 총 가중치의 최솟값을 반환
// 조건
// 1. 문자열 길이 : 1 ≤ numbers.length ≤ 100,000
// 2. numbers는 아라비아 숫자(0~9)로만 구성
// 풀이
// 1. 거리 비례 가중치 계산식(옥타일 거리)
// 2. 완탐 2^100,000 불가
//  => 연산량 줄이기
//   1. 그리디 : 최적의 해가 보장되지 않음.
//   2. DP : dp[i][j], i번 번호를 눌렀을 때 다른 손의 위치 j
//         => i번 번호를 누른 손의 위치는 결국 numbers[i]
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int Diagonal = 3, Straight = 2, INF = 1e9;

int getDist(int cur, int target){
	if (cur == target) return 1; // 제자리 누르기

	int dx = abs(cur % 3 - target % 3);
	int dy = abs(cur / 3 - target / 3);
	return min(dx,dy) * Diagonal + abs(dy - dx) * Straight;
}

int solution(string numbers) {
    int answer = INF;

	int n = numbers.size();
	vector<vector<int>> dp(n+1, vector<int>(12, INF));
	dp[0][3] = dp[0][5] = 0;

	unordered_map<char, int> numToIdx;
	for(int i = 1; i<=9; i++) numToIdx[i + '0'] = i - 1;
	numToIdx['*'] = 9;
	numToIdx['0'] = 10;
	numToIdx['#'] = 11;


	for(int i = 0; i < n; i++){
		int nextIdx = numToIdx[numbers[i]];

		for(int rest = 0; rest<12; rest++){	// 현재 스텝에서 사용하지 않은 손
			if(dp[i][rest] == INF) continue;

			// 1. 이전에 사용한 손으로 이번 스텝 누르기.
			// 이전에 사용한 손
			int prevActive = (i == 0) ? (rest == 3 ? 5 : 3) : numToIdx[numbers[i-1]];
			if(nextIdx != rest)
				dp[i+1][rest] = min(dp[i+1][rest], dp[i][rest] + getDist(prevActive, nextIdx));

			// 2. 이전에 사용하지 않은 손으로 이번 스텝 누르기
			//  => prevActive가 rest(이번에 사용하지 않는 손)이 됨.
			if(nextIdx != prevActive)
				dp[i+1][prevActive] = min(dp[i+1][prevActive], dp[i][rest] + getDist(rest, nextIdx));
		}
	}

	for(int i =0; i<12; i++)
		answer = min(answer, dp[n][i]);

    return answer;
}