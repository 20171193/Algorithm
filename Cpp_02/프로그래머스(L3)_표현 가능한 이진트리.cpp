// 프로그래머스(L3) : 표현 가능한 이진트리
// 조건
// 1. number(1<=number<=10^15)를 이진수로 변환
// 2. 이진수가 이진트리로 표현 가능하면 1, 불가능하면 0
//    - 0은 더미노드, 중위 탐색 순서(좌→루트→우)로 대응
//    - 중위 탐색 1-based 인덱스: 리프=홀수, 내부노드=짝수
// 풀이
// 1. 이진수 변환 후 앞에 0을 패딩해 포화 이진트리 크기(2^k - 1)로 맞춤
// 2. DFS: mid(루트)가 '0'이면 [l,r] 전체가 '0'이어야 유효
//         mid(루트)가 '1'이면 좌/우 서브트리를 재귀 검사
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool dfs(const string& bin, int l, int r) {
    if (l > r) return true;
    int mid = (l + r) >> 1;

    // 부모가 더미일 경우
    if (bin[mid] == '0') {
        // 자식이 더미가 아니라면 불가
        for (int i = l; i <= r; i++) {
            if (bin[i] == '1')
                return false;
        }
        return true;
    }

    // 좌/우 서브트리 확인
    return dfs(bin, l, mid - 1) && dfs(bin, mid + 1, r);
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;

    for (long long num : numbers) {
        string bin;
        // 이진수로 변환
        for (auto n = num; n > 0; n >>= 1)
            bin += (n & 1) + '0';
        reverse(bin.begin(), bin.end());

        // 리프노드 추가 (포화이진트리 포맷), 2^k-1
        int len = 1;
        while (len < bin.size()) len = len * 2 + 1;
        bin = string(len - bin.size(), '0') + bin;

        answer.push_back(dfs(bin, 0, len - 1) ? 1 : 0);
    }

    return answer;
}
