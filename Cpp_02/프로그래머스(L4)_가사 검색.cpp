// 프로그래머스(L4) : 가사 검색
// 문제
// 1. words 배열에 담긴 단어들 중, queries의 각 검색어(키워드) 패턴에 매칭되는
//    단어의 개수를 순서대로 배열로 반환.
// 2. 검색어의 와일드카드 문자 '?'는 임의의 한 글자를 의미.
//    '?'는 검색어의 접두사 또는 접미사 쪽으로만 몰려서 주어짐 (예: "fro??", "????o").
// 3. 매칭 조건 : 길이가 같고, '?'가 아닌 위치의 문자가 모두 일치해야 함.
// 조건
// 1. words : 길이 2 ~ 100,000 / 각 원소 길이 1~10,000자, 중복 없음, 소문자
//    전체 길이 합 2 ~ 1,000,000
// 2. queries : 길이 2 ~ 100,000 / 각 원소 길이 1~10,000자
//    전체 길이 합 2 ~ 1,000,000
//    '?'는 각 검색어의 접두사 아니면 접미사 중 한쪽으로만 등장.
// 풀이
// 1. 접두사 or 접미사 한쪽으로만 등장, 문자 전체 길이 합 10^6이하
//  => 양쪽 트라이 설계(인덱스 기반)
// 결과
// 1. 효율성 실패
//  - 수정 (해결)
//    1. 트라이 bfs탐색 -> 길이 별 트라이(루트 인덱싱)
//    2. isEnd(단어의 끝 확인) -> passCount(노드를 지나는 단어 개수)
//    3. 길이 별 트라이 + passCount
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_LEN = 1000001, ALPHABET_LEN = 26;

int trie[MAX_LEN*2][ALPHABET_LEN];
// 길이 별 루트 인덱싱
int fwdRoots[MAX_LEN], bwdRoots[MAX_LEN];
int passCount[MAX_LEN*2];

int nodeCnt = 0;

// 삽입 전용
int getRoot(bool rev, int len){
	int* roots = rev ? bwdRoots : fwdRoots;
	if(roots[len] == 0)
		roots[len] = ++nodeCnt;

	return roots[len];
}

// 조회 전용
int peekRoot(bool rev, int len){
	return rev ? bwdRoots[len] : fwdRoots[len];
}

// 트라이 삽입
void insert(const string& word) {
	int cur = getRoot(false, word.size());
	int revCur = getRoot(true, word.size());

	passCount[cur]++;
	passCount[revCur]++;

	for(int l =0, r = (int)word.size()-1; l < (int)word.size(); l++, r--){
		int idx = word[l] - 'a';
		int revIdx = word[r] - 'a';

		if(trie[cur][idx] == 0)
			trie[cur][idx] = ++nodeCnt;

		if(trie[revCur][revIdx] == 0)
			trie[revCur][revIdx] = ++nodeCnt;

		cur = trie[cur][idx];
		revCur = trie[revCur][revIdx];

		passCount[cur]++;
		passCount[revCur]++;
	}
}

int matchCount(string query) {
	bool rev = query[0] == '?';
	if(rev) reverse(query.begin(), query.end());

	int cur = peekRoot(rev, (int)query.size());
	if(cur == 0) return 0;

	for(char c : query){
		if(c == '?') break;

		int idx = c - 'a';
		if(trie[cur][idx] == 0)
			return 0;

		cur = trie[cur][idx];
	}

	return passCount[cur];
}


vector<int> solution(vector<string> words, vector<string> queries) {
	vector<int> answer;

	for(const string& word : words)
		insert(word);

	for(string& query : queries)
		answer.push_back(matchCount(query));

    return answer;
}
