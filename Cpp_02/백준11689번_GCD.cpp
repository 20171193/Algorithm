// 백준 11689번 : GCD(n,k)=1
// 조건
// 1. n이 주어졌을 때, GCD(n,k) = 1을 만족하는 자연수 1<=k<=n의 개수
//    (1<=n<=10^12)
//    *n보다 작고 n과의 최대 공약수가 1인 k
//
// 풀이
// 1. n 소인수 분해 -> 포함-배제
#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n;
vector<ll> primes;

// 포함-배제 dfs
void dfs(int idx, ll lcm, int count, ll& result) {
	if (idx == primes.size()) {
		if (count == 0) return;

		ll mtp = n / lcm;
		// 포함-배제 (짝수-, 홀수+)
		if (count % 2 == 1) result += mtp;
		else result -= mtp;

		return;
	}

	// 조합
	// 현재 수 포함
	dfs(idx + 1, lcm * primes[idx], count + 1, result);
	// 현재 수 미포함
	dfs(idx + 1, lcm, count, result);
}

ll solution() {
	ll tempN = n;
	// 소인수 분해
	for (ll i = 2; i * i <= tempN; i++) {
		if (tempN % i == 0) {
			primes.push_back(i);
			while (!(tempN % i)) tempN /= i;
		}
	}
	// 남은 소인수 추가
	if (tempN > 1) primes.push_back(tempN);

	ll result = 0;
	dfs(0, 1, 0, result);

	// 포함-배제
	return n - result;
}

int main() {
	cin >> n;
	cout << solution() << '\n';
	return 0;
}
