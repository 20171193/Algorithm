// 백준 16639번 : 괄호 추가하기(https://www.acmicpc.net/problem/16639)
// 조건
// 1. N(1<=19) : 숫자(ceil(N/2)), 연산자(floor(N/2))
// 2. 정답 범위 (-2^31 < answer < 2^31 )
// 
// 풀이
// 1. 연산자 순열 : 9!
//  => 최적화 고려 : 중복 계산 처리 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <climits>
using namespace std;

typedef long long ll;

int n;
string expr;

ll Calculator(ll a, ll b, char oper) {
	if (oper == '+') return a + b;
	if (oper == '-') return a - b;
	return a * b;
}

ll solution() {
	vector<int> perm(n / 2);
	iota(perm.begin(), perm.end(), 0);

	// 숫자만 따로 캐싱 (계산 결과 누적용)
	vector<ll> nums(n / 2 + 1);
	for (int i = 0; i < expr.size(); i += 2)
		nums[i / 2] = expr[i] - '0';

	ll maxResult = LLONG_MIN;
	do {
		int usedBit = 0;

		vector<ll> numTemp = nums;
		// 결과 값 좌측 할당, 우측 플래그
		for (int i = 0; i < perm.size(); i++) {
			// 원본 배열 인덱스
			int operIdx = perm[i] * 2 + 1;
			// 숫자 배열 인덱스
			int left = perm[i], right = perm[i] + 1;

			// 좌측만 확인
			while (usedBit & (1 << left))
				left--;

			numTemp[left] = Calculator(numTemp[left], numTemp[right], expr[operIdx]);
			usedBit |= (1 << right);
		}

		maxResult = max(maxResult, numTemp[0]);

	} while (next_permutation(perm.begin(), perm.end()));

	return maxResult;
}

int main() {
	cin >> n >> expr;

	if (n == 1)
		cout << expr << '\n';
	else
		cout << solution() << '\n';
}