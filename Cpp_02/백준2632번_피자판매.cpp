// 백준 2632번 : 피자판매
// 조건
// 1. A, B 두 원형 배열에서 뽑아낸 연속된 부분 배열의 합으로
//    입력으로 주어진 수를 만들 수 있는 모든 경우의 수
// 풀이
// 1. A, B 연속된 부분 배열의 합 추출 (중복 따로 카운팅)
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

constexpr int MAX_SIZE = 2000001;
int s, m, n;
vector<int> aVec, bVec;

void SetSum(vector<int>& vec, vector<int>& sums, unordered_set<int>& uset) {
	int length = vec.size();

	int totalSum = 0;
	for (int x : vec)
		totalSum += x;

	sums[totalSum] = 1;
	uset.insert(totalSum);

	for (int i = 0; i < length; i++) {
		int currentSum = 0;
		for (int len = 1; len < length; len++) {
			currentSum += vec[(i + len - 1) % length];
			sums[currentSum]++;
			uset.insert(currentSum);
		}
	}
}

int solution() {
	vector<int> aSums(MAX_SIZE), bSums(MAX_SIZE);
	unordered_set<int> aSet, bSet;
	SetSum(aVec, aSums, aSet);
	SetSum(bVec, bSums, bSet);

	int result = 0;
	if (aSet.find(s) != aSet.end()) result += aSums[s];
	if (bSet.find(s) != bSet.end()) result += bSums[s];

	for (auto iter = aSet.begin(); iter != aSet.end(); iter++) {
		int diff = s - (*iter);

		if (bSet.find(diff) != bSet.end())
			result += aSums[(*iter)] * bSums[diff];
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> s >> m >> n;
	aVec.assign(m, 0);
	bVec.assign(n, 0);
	for (int i = 0; i < m; i++) cin >> aVec[i];
	for (int i = 0; i < n; i++) cin >> bVec[i];

	cout << solution() << '\n';
	return 0;
}