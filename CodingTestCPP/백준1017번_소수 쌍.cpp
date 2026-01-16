// 백준 1017번 : 소수 쌍(https://www.acmicpc.net/problem/1017)
// 조건
// 1. 리스트의 수를 짝지어 각 쌍의 합이 소수가 되게 만들어야 함.
// 2. 모든 수를 다 짝지었을 때, 첫 번째 수와 어떤 수를 짝지었는지 오름차순 출력
//  2-1. ex) {1, 4, 7, 10, 11, 12}를 조건에 맞게 짝짓는 경우는 두 가지
//        1. (1-4), (7-10), (11-12)
//        2. (1-10), (4-7), (11-12)
//  2-2. 각 경우에서 첫 번째 수(1)과 쌍이 되는 수는 오름차 순으로 4, 10
// 3. 리스트의 크기(N<=50, 짝수)
// 4. 리스트 안의 수(1<=V<=1000), 중복 x 
// 
// 풀이
// 1. 1<=P<=2000 범위의 소수 미리 할당(에라토스테네스의 체)
// 2. 소수 조건
//  2-1. 소수가 아닌 수
//    - 홀+홀 = 짝(2 제외)
//    - 짝+짝 = 짝
//  2-2. 즉, 홀+짝 조합에서만 가능
// 3. 이분 매칭 (홀+짝 조합에서 이분 매칭)
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

int n, arr[51], matched_opp[26];
vector<int> results, odd, even;
vector<vector<int>> graph;
bool isPrime[2001], used_opp[26];

// 에라토스테네스의 체
void PrimeFormat() {
	memset(isPrime, true, sizeof(isPrime));

	isPrime[0] = isPrime[1] = false;
	for (int i = 0; i * i <= 2000; i++) {
		if (isPrime[i]) {
			// i 이상의 수만 처리 (i*i)~
			for (int j = i * i; j <= 2000; j += i) {
				isPrime[j] = false;
			}
		}
	}
}

// 이분 매칭 
bool canMatch(int ognIdx) {
	for (int oppIdx : graph[ognIdx]) {
		if (used_opp[oppIdx]) continue;

		used_opp[oppIdx] = true;
		// 연결가능한 짝을 만난 경우 성공
		if (matched_opp[oppIdx] == -1 || canMatch(matched_opp[oppIdx])) {
			matched_opp[oppIdx] = ognIdx;
			return true;
		}
	}
	return false;
}

void solution() {
	// 2000이하의 소수 미리 할당
	PrimeFormat();

	// 리스트를 홀/짝으로 구분
	for (int i = 0; i < n; i++) {
		if (arr[i] % 2 == 0) even.push_back(arr[i]);
		else odd.push_back(arr[i]);
	}

	// 홀-짝의 개수가 다른 경우
	if (even.size() != odd.size())
		return;

	// 첫번째 수를 기준으로 참조 할당
	vector<int>& origin = arr[0] % 2 == 0 ? even : odd;
	vector<int>& opposite = arr[0] % 2 == 0 ? odd : even;

	// 단방향 인접리스트 (쌍이 소수가 되는 경로 미리 할당)
	graph.assign(origin.size(), {});
	for (int i = 0; i < origin.size(); i++) {
		for (int j = 0; j < opposite.size(); j++) {
			if (isPrime[origin[i] + opposite[j]])
				graph[i].push_back(j);
		}
	}

	// 첫번째 수 매칭
	for (int oppIdx : graph[0]) {
		memset(matched_opp, -1, sizeof(matched_opp));

		int matchCount = 1;
		// 나머지 매칭
		for (int ognIdx = 1; ognIdx < origin.size(); ognIdx++) {
			memset(used_opp, false, sizeof(used_opp));
			used_opp[oppIdx] = true;

			if (canMatch(ognIdx)) matchCount++;
		}

		// 모든 쌍을 연결한 경우
		if (matchCount == n / 2) results.push_back(opposite[oppIdx]);
	}

	// 결과 오름차 정렬
	sort(results.begin(), results.end());
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	solution();

	if (results.empty())
		cout << -1 << '\n';
	else {
		for (int ans : results)
			cout << ans << ' ';
		cout << '\n';
	}
	return 0;
}