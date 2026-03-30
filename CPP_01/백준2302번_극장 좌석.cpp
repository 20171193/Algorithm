// 백준 2302번 : 극장 좌석(https://www.acmicpc.net/problem/2302)
// 조건
// 1. N번 입장권으로 N-1, N, N+1에 앉을 수 있음.
// 2. VIP 회원은 반드시 자기 좌석에 앉아야함.
// 3. VIP 회원의 좌석 번호가 주어졌을 때, 사람들이 좌석에 앉는 서로 다른 방법의 가짓 수
// 
// 풀이
// 1. n번을 배치하는 경우의 수 
//  1-1. f(1) = 1 
//       f(2) = 2 (1-2, 2-1)
//       f(3) = 3 (1-2-3, 2-1-3, 1-3-2)
//       f(4) = 5 (1-2-3-4, 2-1-3-4, 1-3-2-4, 1-2-4-3, 2-1-4-3)
//       피보나치 수
// 2. vip처리
//  2-1. vip를 기준으로 점화식이 끊김.
//  2-2. vip 인덱스를 기준으로 구간 별 경우의 수 *
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, fibo[41], section[41], vip[42];

int solution() {
	int answer = 1;

	int maxDist = 0, prev = 0;
	vip[m] = n + 1;	// 마지막 구간 처리
	for (int i = 0; i <= m; i++) {
		section[i] = vip[i] - prev - 1;
		maxDist = max(maxDist, section[i]);	// 가장 긴 구간 할당
		prev = vip[i];
	}

	// 가장 긴 구간까지 피보나치 수
	fibo[0] = fibo[1] = 1;
	for (int i = 2; i <= maxDist; i++)
		fibo[i] = fibo[i - 2] + fibo[i - 1];

	// 구간 별 경우의 수 곱
	for (int i = 0; i <= m; i++)
		answer *= fibo[section[i]];

	return answer;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++)
		cin >> vip[i];

	cout << solution() << '\n';
	return 0;
}