// 백준 1339번 : 단어 수학
// 조건
// 1. 알파벳을 0~9의 숫자로 치환한 뒤, 주어진 단어를 더했을 때
//    나올 수 있는 최댓값
// 2. 단어 개수 N(1<=N<=10), 수의 최대 길이 8 
// 
// 풀이
// 1. 그리디
//  1-1. 각 단어별로 자릿수 누적(가중치)
// 2. 10^8 * 10 -> int 불가 long long 사용
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n;
ll weight[27];
string words[10];

ll solution() {
	ll ret = 0;
	// 문자별 가중치 할당
	for (int i = 0; i < n; i++) {
		for (int j = (int)words[i].size() - 1, digit = 1; j >= 0; j--, digit *= 10) {
			weight[words[i][j] - 'A'] += digit;
		}
	}

	sort(weight, weight + 27, greater<ll>());

	// 가중치순으로 9~0 치환, 결과 누적
	int num = 9;
	for (int i = 0; i < 27; i++) {
		if (!weight[i]) break;
		ret += weight[i] * num--;
	}
	return ret;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> words[i];

	cout << solution();
	return 0;
}