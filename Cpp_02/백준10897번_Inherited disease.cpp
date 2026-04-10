// 백준 10897번 : Inherited disease
// 조건
// 1. n세대는 n+1만큼의 자식을 남김.
// 2. 순서에 따라 번호가 매겨짐.
// 3. d(i) : i-1 세대의 노드가 d(i)번째로 낳은 자식의 번호
// 4. 세대 d(1<=d<=100)
// 풀이
// 1. 특정 깊이에서 노드의 순번 찾기
// 2. n깊이의 노드 총 개수 cnt[n] = (n-1) * n 
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

constexpr int MOD = 1000000007;
int d, arr[101];

vector<ll> solution() {
	vector<ll> result;

	// 각 세대별 시작 노드번호, 깊이별 노드 개수
	vector<ll> depthStartNum(d + 1), nodeCounts(d + 1);

	depthStartNum[0] = 0;
	nodeCounts[0] = 1;
	for (ll i = 1; i <= d; i++) {
		nodeCounts[i] = (nodeCounts[i - 1] * i) % MOD;
		depthStartNum[i] = (depthStartNum[i - 1] + nodeCounts[i - 1]) % MOD;
	}

	arr[0] = 1;
	for (int i = 1; i <= d; i++) {
		// 현재 세대(i)에서 노드의 순서
		int curOrder = (arr[i - 1] - 1) * i + arr[i];
		result.push_back((depthStartNum[i] + curOrder - 1) % MOD);
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> d;
	for (int i = 1; i <= d; i++)
		cin >> arr[i];

	for (ll ans : solution())
		cout << ans << '\n';
	return 0;
}