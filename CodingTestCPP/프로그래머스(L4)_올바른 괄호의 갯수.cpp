#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Ä«Å»¶õ ¼ö
// 1 2 5 14
// f(1) = f(0) * f(0)
// f(2) = f(0) * f(1)
//       +f(1) * f(0)
// f(3) = f(0) * f(2)
//       +f(1) * f(1)
//       +f(2) * f(0)
//....
int dp[15];

int solution(int n) {
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            dp[i] += dp[j] * dp[i - 1 - j];

    return dp[n];
}