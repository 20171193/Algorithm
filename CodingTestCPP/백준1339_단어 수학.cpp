// 백준 1339번 : 단어 수학
// 조건
// 1. 알파벳을 0~9의 숫자로 치환한 뒤, 주어진 단어를 더했을 때
//    나올 수 있는 최댓값
// 2. 단어 개수 N(1<=N<=10), 수의 최대 길이 8 
// 
// 풀이
// 1. 그리디
//  1-1. 자릿수별로 단어 분류
//  1-2. 단어별로 차수 할당 (자릿수)
//  1-3. 분류된 단어 차수 기준 내림차 정렬
//  1-4. 높은 자릿수, 높은 차수부터 9~0 치환
// 2. 10^8 * 10 -> int 불가 long long 사용
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, num = 9;
bool used[27];
ll degree[27];
string words[10];

ll solution() {
	vector<vector<int>> digitNum(9);

	// 차수 할당, 자릿수별 문자 할당
	for (int i = 0; i < n; i++) {
		int digit = 0;
		for (auto iter = words[i].rbegin(); iter != words[i].rend(); iter++, digit++) {
			int ascii = (*iter) - 'A';

			degree[ascii] += pow(10, digit);
			digitNum[digit].push_back(ascii);
		}
	}

	// 문자 치환 + 결과 누적
	ll result = 0;
	for (auto iter = digitNum.rbegin(); iter != digitNum.rend(); iter++) {
		if ((*iter).empty()) continue;

		// 차수 기준 정렬
		sort((*iter).begin(), (*iter).end(), [](int a, int b) { return degree[a] > degree[b]; });

		for (int ascii : (*iter)) {
			if (!used[ascii]){
				result += ascii * degree[ascii];
				used[ascii] = true;
			}
		}
	}

	return result;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> words[i];

	cout << solution();
	return 0;
}