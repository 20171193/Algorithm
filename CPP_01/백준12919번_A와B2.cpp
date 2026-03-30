// 백준 12919번 : A와 B 2 (https://www.acmicpc.net/problem/12919)
// 조건
// 1. S를 T로 바꾸는 게임
//  1-1. 방식
//     - 문자열 뒤에 A추가
//     - 문자열 뒤에 B추가 후 뒤집기
// 2. 바꿀 수 있으면 1, 없으면 0출력
// 
// 풀이
// 1. 정방향 완탐
//  - 불가 (2^n)
// 2. 역방향 탐색 (가능한 탐색만 가지치기)
//  - 문자열 뒤에서 A제거
//  - 뒤집고 문자열 앞에 B제거
// ***'뒤집어야 한다'는 조건이 힌트***
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool solution(string target, string cur) {
	if (target.size() >= cur.size())
		return target == cur;

	bool result = false;

	if (cur.back() == 'A')
		result |= solution(target, cur.substr(0, cur.size() - 1));

	if (cur.front() == 'B') {
		reverse(cur.begin(), cur.end());
		cur.pop_back();
		result |= solution(target, cur);
	}

	return result;
}

int main() {
	string s, t;
	cin >> s >> t;

	if (solution(s, t)) cout << 1 << '\n';
	else cout << 0 << '\n';
	return 0;
}