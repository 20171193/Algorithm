// 백준 3649번 : 로봇 프로젝트(https://www.acmicpc.net/problem/3649)
// 조건
// 1. 구멍의 너비x(1<=x<=20), x는 정수
//  1-1. 두 조각의 길이의 합이 구멍의 너비와 일치해야 함. 
// 2. 여러 레고 조각 중 구멍을 막을 수 있는 두 조각을 구하라
//  2-1. 레고 조각의 수(0<=n<=1,000,000), 단위(나노미터)l (1<=l<=100,000,000)
//  2-2. 정답이 여러 개인 경우는 |l1 - l2|가 가장 큰 것 출력
// 
// 풀이
// 1. 구멍의 너비x(센치미터) -> 나노미터 변환 
// 2. 조각 정렬 후 투 포인터 O(n)
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

constexpr int nm = 10000000;
const string danger = "danger";

int x, n, arr[1000001];

void solution() {
	int nmx = x * nm;

	sort(arr, arr + n);

	int l = 0, r = n - 1;
	while (l < r) {
		int sum = arr[r] + arr[l];
		if (sum == nmx) {
			cout << "yes " + to_string(arr[l]) + ' ' + to_string(arr[r]) << '\n';
			return;
		}
		else if (sum < nmx) l++;
		else r--;
	}

	cout << danger << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	while (cin >> x >> n) {
		for (int i = 0; i < n; i++)
			cin >> arr[i];

		solution();
	}

	return 0;
}
