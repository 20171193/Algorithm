// 백준 2957번 : 이진 탐색 트리
// 조건
// 1. 1<= num <= N(1<=N<=300,000)인 num으로 이뤄진 수열이 입력으로 주어짐(중복x)
//    이 수열로 이진 탐색 트리를 만들어야 함.
// 2. 첫번째 수를 루트로 나머지 수들을 순서대로 삽입.
// 3. 삽입은 insert(x, root)함수로 진행됨.
//  insert(number X, node N)
//   - 카운터 C값을 1 증가시킨다
//   - if X가 노드 N에 있는 수보다 작다면
//		- if N의 왼쪽 자식이 없다면
//			 - X를 포함하는 새 노드를 만든 뒤, N의 왼쪽 자식으로 만든다
//		- else
//			 - insert(X, N의 왼쪽 자식)
//   - else (X가 노드 N에 있는 수보다 크다면)
//		- if N의 오른쪽 자식이 없다면
//			 - X를 포함하는 새 노드를 만든 뒤, N의 오른쪽 자식으로 만들기
//		- else
//			 - insert(X, N의 오른쪽 자식)
// 4. 각 수를 삽입한 후에 C의 값을 출력
// 풀이 
// 1. bst 구현 O(N^2) 불가
// 2. 정렬 자료구조 + 깊이 메모이제이션
//    => 중복 없는 입력 : set(nlogn)
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, arr[300001];
ll depth[300001];

void solution() {
	ll cnt = 0;
	set<int> s;	// 중복 없는 입력

	for (int i = 0; i < n; i++) {
		auto it = s.lower_bound(arr[i]);	// 같거나 큰 수

		int l = -1, r = -1;
		if (it != s.end()) r = *it;
		if (it != s.begin()) l = *prev(it);

		// 깊이 메모이제이션
		depth[arr[i]] = max(l == -1 ? -1 : depth[l], r == -1 ? -1 : depth[r]) + 1;
		// cnt 누적
		cnt += depth[arr[i]];
		cout << cnt << '\n';

		s.insert(arr[i]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	solution();
	return 0;
}