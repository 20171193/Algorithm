// 백준 15824번 : 너 봄에는 캡사이신이 맛있단다
// 조건
// 1. 주헌고통지수 : 음식 조합에서 가장 높은 수치 - 가장 낮은 수치
// 2. 중복없는 조합
// 3. 메뉴의 개수 N(1<=N<=300,000)
// 4. 스코빌 지수 s(0<=s<=2^31-1)
// 풀이
// 1. 정렬
// 2. i가 최솟/최댓값으로 사용될 경우의 수
//   - 최댓값 2^n : 0~i
//   - 최솟값 2^(n-i-1) : i+1~n 
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
constexpr ll MOD = 1000000007;

int n, scovilles[300001];

int solution() {
	vector<ll> modPow(n + 1);
	modPow[0] = 1;
	for (int i = 1; i < n; i++)
		modPow[i] = ((ll)(modPow[i - 1] * 2) % MOD);

	sort(scovilles, scovilles + n);

	ll result = 0;
	for (int i = 0; i < n; i++)
		result = (result + (scovilles[i] * (modPow[i] - modPow[n - i - 1] + MOD) % MOD)) % MOD;

	return (int)(result % MOD);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> scovilles[i];

	cout << solution() << '\n';
	return 0;
}