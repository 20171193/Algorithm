// 프로그래머스(L3) : 최적의 행렬 곱셈
// 문제
// 1. 모든 행렬을 곱하기 위한 최소 곱셈 연산의 개수 리턴
// 조건
// 1. 행렬 개수 (3<=matrix_sizes.size()<=200)
// 2. 행/열 크기 (3<=length<=200)
// 3. 계산을 할 수 없는 행렬은 입력으로 주어지지 않음.
// 풀이
// 1. 행/열 중 큰 수 우선 정렬
// 2. 행렬 곱셈 계산
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

struct Comp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        int mxa = max(a.first, a.second);
        int mxb = max(b.first, b.second);
        if (mxa == mxb)
            return a.first == mxa;
        return mxa < mxb;
    }
};

int solution(vector<vector<int>> matrix_sizes) {
    int answer = 0;

    vector<vector<int>>& mts = matrix_sizes;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;

    for (const auto& v : mts) pq.push({ v[0], v[1] });

    // 항상 연산이 가능
    while (!pq.empty()) {
        auto left = pq.top();
        pq.pop();

        if (pq.empty()) {
            answer += left.first * left.second;
            break;
        }

        auto right = pq.top();
        pq.pop();

        answer += left.first * left.second * right.second;
        pq.push({ left.first, right.second });
    }

    return answer;
}

int main() {
    cout << solution({ {5,3}, {3,10},{10,6} });
    return 0;
}