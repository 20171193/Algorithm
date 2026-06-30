// 프로그래머스(L3) : 주사위 고르기
// 문제
// 1. A, B가 각각 n/2 개의 주사위를 가져가 굴리고
//    나온 수들을 모두 합해 점수를 계산함.
// 2. A가 승리할 확률이 가장 높아지도록 주사위를 가져갈 때,
//    가져가야할 주사위의 번호를 오름차순으로 출력
// 조건
// 1. 주사위 개수 : 2<=dice.size()<=10 (2의 배수)
// 2. 각 면에 쓰인 수 : 1<=num<=100
// 풀이
// 1. 직접 비교 불가 : 주사위 조합(10c5=252) * 합 경우의 수(6^10) 
// 2. 합 리스트 + 이분 탐색
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(const int mask, int depth, int sum, vector<int>& sums, const vector<vector<int>>& dice) {
    if (depth >= dice.size() / 2) {
        sums.push_back(sum);
        return;
    }

    int diceIndex = -1;
    for (int i = 0; i < dice.size(); i++) {
        if (mask & (1 << i)) diceIndex++;
        if (diceIndex == depth) {
            diceIndex = i;
            break;
        }
    }

    for (int i = 0; i < 6; i++)
        dfs(mask, depth + 1, sum + dice[diceIndex][i], sums, dice);
}

int lowerBound(int left, int right, int num, vector<int>& arr) {
    while (left < right) {
        int mid = (left + right) >> 1;
        if (arr[mid] < num)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

vector<int> solution(vector<vector<int>> dice) {
    vector<int> answer;

    int size = dice.size();
    vector<int> comb(size);
    for (int i = size / 2; i < size; i++) comb[i] = 1;

    int mxWinCount = 0;
    int mxMask = 0;
    do {
        // 주사위 조합 비트마스킹
        int aMask = 0, bMask = 0;
        for (int i = 0; i < comb.size(); i++) {
            aMask |= (comb[i] << i);
            bMask |= (1 - comb[i] << i);
        }

        // 각 마스킹에 따른 합 경우의 수
        vector<int> aSums, bSums;
        dfs(aMask, 0, 0, aSums, dice);
        dfs(bMask, 0, 0, bSums, dice);

        sort(bSums.begin(), bSums.end());

        // 이분 탐색
        int winCount = 0;
        for (int aSum : aSums)
            winCount += lowerBound(0, bSums.size(), aSum, bSums) - 1;

        if (winCount > mxWinCount) {
            mxMask = aMask;
            mxWinCount = winCount;
        }
    } while (next_permutation(comb.begin(), comb.end()));


    // 정답 마스크 할당
    for (int i = 0; i < size; i++)
        if (mxMask & (1 << i))
            answer.push_back(i + 1);

    return answer;
}