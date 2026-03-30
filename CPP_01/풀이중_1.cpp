// 백준 14268번 : 회사 문화 2 (https://www.acmicpc.net/problem/14268)
// 조건
// 1. 내리 칭찬 (자식 노드 모두)
// 2. 쿼리
//  2-1. 1 i w : i가 w만큼의 칭찬을 받음
//  2-2. 2 i : i가 칭찬 받은 정도를 출력
// 3. 노드(n<=100,000), 쿼리(m<=100,000), 칭찬(w<=1,000)
//
// 풀이
// 1. 구간합 : 세그먼트 트리
// 2. 1 쿼리마다 모든 구간 갱신 가능 -> O(N) 불가
//   : 1 쿼리 (갱신 대기)
//   : 2 쿼리 (갱신 후 출력) 
// 

// ******세그먼트 트리 학습하기
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int n, m, parents[100001], weights[100001];
bool updated[100001];
vector<vector<int>> querys;

// 세그먼트 트리 전역
ll seg_tree[400004], pendings[400004];

// 서브 트리 갱신
void UpdateTree(int start, int end, int node, int index, ll diff) {
	// 보류 확인
	CheckPending(start, end, node);


}
ll GetSum(int start, int end, int node, int left, int right) {

}

// 보류 확인
void CheckPending(int start, int end, int node) {
	if (pendings[node] == 0) return;

	// 루트 갱신
	seg_tree[node] += (end - start + 1) * pendings[node];
	// 서브트리 보류 할당
	if (start != end) {
		int left = node * 2, right = node * 2 + 1;
		pendings[left] += pendings[node];
		pendings[right] += pendings[node];
	}

	pendings[node] = 0;
}

void solution() {
	for (int i = 0; i < m; i++) {
		int type = querys[i][0];
		int idx = querys[i][1];
		int weight = querys[i][2];

		if (type == 1)
			weights[idx] += weight;
		else
			cout << GetCost(idx) << '\n';

		updated[idx] = true;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> parents[i];

	querys.assign(m, vector<int>(3));
	for (int i = 0; i < m; i++) {
		cin >> querys[i][0] >> querys[i][1];
		if (querys[i][0] == 1)
			cin >> querys[i][2];
	}

	solution();
	return 0;
}