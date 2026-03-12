// 백준 23831번 : 나 퇴사임?
// 조건
// 1. 선택지
//  1-1. 요양 : 최대 A회
//  1-2. 정독실/소학습실 : B회 미만 -> 퇴사
//  1-3. 휴게실 : 2일 연속 -> 퇴사
// 2. 자습일N(1<=N<=100), (0<=A,B<=N)
// 3. 만족도(1<=p,q<=r<=s<=100)
//  : 정독실p,소학습실q,휴게실r,요양s
// 4. 규칙을 지키면서 N일 동안 얻을 수 있는 만족도의 합의 최댓값
//
// 풀이
// 1. DP : 상태 메모이제이션
//  1-1. dp[날짜][요양 횟수][학습 횟수][자습]
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int READ_ROOM = 0, STUDY_ROOM = 1, SELF_ROOM = 2, REST = 3;

int n, a, b, satis[101][4], dp[101][101][101][2];

int solution() {
	dp[0][0][0][0] = dp[0][0][0][1] = 1;

	for (int day = 1; day <= n; day++) {
		for (int rest = 0; rest <= a; rest++) {
			for (int study = 0; study <= b; study++) {
				for (int self = 0; self <= 1; self++) {
					if (!dp[day - 1][rest][study][self]) continue;

					// 정독실 / 소학습실
					dp[day][rest][min(b, study + 1)][0] = max(dp[day][rest][min(b, study + 1)][0]
						, dp[day - 1][rest][study][self] + max(satis[day][READ_ROOM], satis[day][STUDY_ROOM]));

					// 요양
					if (rest < a) {
						dp[day][rest + 1][study][0] = max(dp[day][rest + 1][study][0]
							, dp[day - 1][rest][study][self] + satis[day][REST]);
					}
					// 자습
					if (self == false) {
						dp[day][rest][study][true] = max(dp[day][rest][study][true]
							, dp[day - 1][rest][study][false] + satis[day][SELF_ROOM]);
					}
				}
			}
		}
	}

	int ret = 0;
	// 최종적으로 모든 요양 횟수 확인
	for (int rest = 0; rest <= a; rest++)
		ret = max({ ret, dp[n][rest][b][false], dp[n][rest][b][true] });

	// 초기 상태를 1로 시작
	return ret - 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 4; j++)
			cin >> satis[i][j];

	cout << solution() << '\n';
	return 0;
}
