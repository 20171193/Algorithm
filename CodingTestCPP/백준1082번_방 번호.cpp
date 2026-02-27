// 백준 1082번 : 방 번호
// 조건
// 1. 숫자 N(1<=N<=10)
// 2. 소지한 돈 M(1<=M<=50)
// 3. 숫자 별 금액 P(1<=P<=50)
// 4. 돈을 최대로 사용해 만들 수 있는 가장 큰 방 번호
// 풀이
// 1. 만들 수 있는 최대 자릿수
// 2. 최대 금액
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, m, p[11];

string solution() {
	if (n == 1) return "0";

	// 최소 비용의 숫자 찾기
	// 해당 수가 0이라면 그 다음 비용의 숫자 찾기
	int fstMinNum = 0, scdMinNum = -1;
	for (int i = 0; i < n; i++) {
		if (p[fstMinNum] >= p[i]) fstMinNum = i;

		if (i > 0 && (scdMinNum == -1 || p[scdMinNum] >= p[i])) scdMinNum = i;
	}

	// 0 제외 살 수 있는 수가 없을 경우
	if (scdMinNum == -1 || p[scdMinNum] > m) return "0";

	// m을 모두 사용해 만들 수 있는 최대 자릿 수 
	int digits = (m - p[scdMinNum]) / p[fstMinNum] + 1;
	string result(1, scdMinNum + '0');
	result.append(digits - 1, fstMinNum + '0');

	// 남은 비용
	int cost = m - (p[scdMinNum] + (digits - 1) * p[fstMinNum]);

	// 가장 큰 수부터 대입 
	// O(digits * n) : 최대 50*10
	bool endFlag = false;
	for (int i = 0; i < result.size(); i++) {
		int num = result[i] - '0';
		for (int j = n - 1; j >= 0; j--) {
			// 현재 자릿수 변경
			if (j > num && cost >= p[j] - p[num]) {
				cost -= p[j] - p[num];
				result[i] = j + '0';
				break;
			}
		}
	}

	return result;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> p[i];
	cin >> m;

	cout << solution() << '\n';
	return 0;
}