// 백준 1253번 : 좋다(https://www.acmicpc.net/problem/1253)
// 조건
// 1. n개(n<=2,000)의 수에서 다른 두 수의 합으로 나타낼 수 있는 수의 개수
// 2. arr[i]<=1,000,000,000 (중복, 음수)
// 
// 풀이
// 1. 정렬, 투포인터 풀이
//  1-1. n^2 : 약 4,000,000
#include <iostream>
#include <algorithm>
using namespace std;

int n, arr[2001];

int solution() {
	int answer = 0;
	sort(arr, arr + n);

	for (int i = 0; i < n; i++) {
		// 투 포인터 풀이
		int l = 0, r = n - 1;
		while (l < r) {
			int sum = arr[l] + arr[r];
			if (sum == arr[i]) {
				// 현재 인덱스가 조합에 포함되지 않아야 함.
				if (l != i && r != i) {
					answer++;
					break;
				}
				else if (l == i) l++;
				else if (r == i) r--;
			}
			else if (sum < arr[i]) l++;
			else r--;
		}
	}

	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	cout << solution();
	return 0;
}