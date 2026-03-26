// 백준 1029번 : 그림 교환
// 조건
// 1. 그림을 팔 때, 산 가격 이상으로 팔아야 함.
// 2. 같은 그림을 두 번 이상 못삼.
// 3. 그림을 소유했던 사람의 수의 최댓값
// 풀이
// 1. 비용이 증가하는 경로로 최대한 많은 노드를 방문 
// 2. 중복 방문은 안됨. (조건 2)
// 3. dfs + dp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

constexpr int INF = 151;

int n, ret = -1, arr[15][15], dp[15][1<<15];

void solution(int node, int cost, int mask, int cnt){
    // dp 기저조건
    if(dp[node][mask] <= cost) 
        return;

    dp[node][mask] = cost;
    ret = max(ret, cnt);

    for(int i =0; i<n; i++){
        if(mask & (1 << i) || arr[node][i] < cost)  continue;
        solution(i, arr[node][i], mask | (1 << i), cnt + 1);
    }
    return; 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    string temp;
    for(int i =0; i < n; i++){
        cin >> temp;
        for(int j =0; j< n; j++)
            arr[i][j] = temp[j] - '0';

        fill(&dp[i][0], &dp[i][0] + (1 << n), INF);
    }

    solution(0, 0, 1, 1);

    cout << ret << '\n';
    return 0;
}