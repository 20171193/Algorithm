// 백준 16565번 : N포커
// 조건
// 1. 52장의 카드에서 n장을 뽑아 포카드를 만들면 플레이어가 승, 아니면 딜러의 승
// 2. 플레이어가 이기는 경우의 수를 10,007로 나눈 나머지를 출력
// 3. 카드 : 문양4개, 숫자 13개
// 풀이
// 1. 조합(파스칼)
#include <iostream>
using namespace std;

typedef long long ll;

constexpr int MOD = 10007, CARD_COUNT = 52;
int n, comb[CARD_COUNT + 1][CARD_COUNT + 1];

// 조합 개수(파스칼 삼각형)
void initComb() {
	for (int i = 0; i <= 52; i++) {
		comb[i][0] = comb[i][i] = 1;

		for (int j = 1; j < i; j++) {
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
		}
	}
}


int solution() {
	initComb();

	int successCount = n / 4;	// 만들 수 있는 포카드 개수
	if (!successCount) return 0;

	int result = 0;
	for (int cnt = 1; cnt <= successCount; cnt++) {
		int choose = 4 * cnt;		// 포카드에 속한 카드 개수
		int remain = n - choose;	// 포카드를 제외한 남은 카드 개수

		ll temp = (ll)comb[13][cnt] * comb[CARD_COUNT - choose][remain] % MOD;

		// 포함-배제
		if (cnt % 2 == 1) result = (result + temp) % MOD;
		else result = (result - temp + MOD) % MOD;
	}

	return result;
}

int main() {
	cin >> n;
	cout << solution() << '\n';
	return 0;
}