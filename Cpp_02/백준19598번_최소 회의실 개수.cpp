// 백준 19598번 : 최소 회의실 개수
// 조건
// 1. 회의 총 N(1<=N<=100,000)
// 2. 동시에 진행불가. 최소 회의실 개수 출력
// 풀이
// 1. 정렬 + 우선순위 큐
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n;
pair<int, int> arr[100001];

int solution() {
	// 시작시간 기준 오름차 
	sort(arr, arr + n);

	// 종료시간 min-heap
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 0; i < n; i++) {
		if (!pq.empty() && pq.top() <= arr[i].first) pq.pop();
		pq.push(arr[i].second);
	}

	return pq.size();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i].first >> arr[i].second;

	cout << solution() << '\n';
	return 0;
}