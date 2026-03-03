// 백준 1021번 : 회전하는 큐
// 조건 
// 1. 큐, 회전
// 2. 특정 원소를 뽑는데 최소 회전 수
//  2-1. 원소의 개수와 위치가 주어짐.
// 3. 큐 크기N(1<=N<=50)
// 4. 뽑을 원소 개수M(1<=M<=N)
// 풀이
// 1. 덱
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int n, m, arr[51];

int solution() {
	int ret = 0;
	deque<int> dq;
	for (int i = 1; i <= n; i++) dq.push_back(i);

	for (int i = 0; i < m; i++) {
		auto iter = find(dq.begin(), dq.end(), arr[i]);
		int dist = iter - dq.begin();

		// 가까운쪽으로 회전
		int leftRot = dist, rightRot = dq.size() - dist;
		// 좌회전
		if (leftRot <= rightRot) {
			ret += leftRot;
			while (leftRot--) {
				dq.push_back(dq.front());
				dq.pop_front();
			}
		}
		// 우회전
		else {
			ret += rightRot;
			while (rightRot--) {
				dq.push_front(dq.back());
				dq.pop_back();
			}
		}

		dq.pop_front();
	}

	return ret;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++)
		cin >> arr[i];
	cout << solution() << '\n';
	return 0;
}