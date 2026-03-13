// 백준 4237번 : 비 단조성
// 조건
// 1. 수열 A에서 B[0] > B[1] < B[2]....를 만족하는 수열 B를 찾기
// 2. 원소 몇 개를 삭제해서 해당 수열을 만들어야 함.
// 3. B의 최대 길이 출력
// 4. A의 길이는 최대 30,000
// 풀이
// 1. 부등호 방향을 차이로 판별(vec[i] - vec[i-1])
// 2. 서로 다른 방향일때 카운팅
#include <iostream>
#include <vector>
using namespace std;

int t, n, answer[51];

int solution(const vector<int>& vec) {
	int size = vec.size();
	if (size < 2) return size;

	int ret = 1, dir = 1;	// >부터 시작
	for (int i = 1; i < size; i++) {
		int diff = vec[i] - vec[i - 1];
		if (diff == 0) continue;

		int cur = diff > 0 ? 1 : -1;

		if (cur != dir) {
			ret++;
			dir = cur;
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;

	for (int i = 0; i < t; i++) {
		cin >> n;
		vector<int> vec(n);
		for (int j = 0; j < n; j++) cin >> vec[j];
		answer[i] = solution(vec);
	}

	for (int i = 0; i < t; i++)
		cout << answer[i] << '\n';
	return 0;
}