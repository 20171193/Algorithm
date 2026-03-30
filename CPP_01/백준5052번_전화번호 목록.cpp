// 백준 5052번 : 전화번호 목록(https://www.acmicpc.net/problem/5052)
// 조건
// 1. 목록의 일관성 유지
//  1-1. 일관성 있는 목록 : 어떤 번호도 다른 번호의 접두어가 아닌 경우
//
// 풀이
// 1. 정적 배열 트라이
//  1-1. n
// 2. 그냥 문자열 정렬(접두어끼리 정렬됨)
//  2-1. n * log(n)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

constexpr int MAX_NODE = 100010;

int trie[MAX_NODE][10];
bool isEnd[MAX_NODE];

int t, n;
string numbers[10001], answer[51];

// 트라이 구조 풀이
string Trie() {
	int nodeCount = 0;
	bool searchEndFlag = true;

	for (int i = 0; i < n; i++) {
		int cur = 0; // 루트노드부터 시작
		bool addFlag = false;
		for (auto& nc : numbers[i]) {
			int next = nc - '0';

			// 경로가 없는 경우
			if (!trie[cur][next]) {
				trie[cur][next] = ++nodeCount;
				addFlag = true;
			}

			cur = trie[cur][next];

			// 짧은 번호 경로 발견
			if (isEnd[cur]) {
				searchEndFlag = false;
				break;
			}
		}
		isEnd[cur] = true;

		// 긴 번호 경로 발견
		if (!addFlag) {
			searchEndFlag = false;
			break;
		}
	}

	memset(trie, 0, (nodeCount + 1) * 10 * sizeof(int));
	memset(isEnd, false, (nodeCount + 1) * sizeof(bool));;

	// 탐색 중간에 종료된 경우 (접두어 찾은 경우)
	if (!searchEndFlag) return "NO";

	return "YES";
}

// 단순 문자열 정렬 풀이
string Sort() {
	// 문자열 정렬
	sort(numbers, numbers + n);

	for (int i = 1; i < n; i++) {
		if (numbers[i].size() > numbers[i - 1].size()
			&& numbers[i].substr(0, numbers[i - 1].size()) == numbers[i - 1])
			return "NO";
	}
	return "YES";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	int tc = 0;
	while (tc < t) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> numbers[i];

		//answer[tc++] = Sort();
		answer[tc++] = Trie();
	}

	for (int i = 0; i < t; i++)
		cout << answer[i] << '\n';

	return 0;
}