// 백준 1025번 : 제곱수 찾기(https://www.acmicpc.net/problem/1025)
// 조건
// 1. n*m
// 2. 1개 이상의 칸을 선택. 
//  2-1. 행/열의 번호가 선택한 순서대로 등차수열을 이뤄야 함
//  2-2. 선택한 칸에 적힌 수를 이어붙인 정수 중, 가장 큰 완전 제곱수를 구하라
//      *완전 제곱수 : 어떤 정수를 제곱한 수 
// 
// 풀이
// 1. 모든 경우의 수 + sqrt
#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;
typedef long double ld;

int n, m;
string board[10];

bool isSquare(ll num) {
	if (num < 0) return false;
	ll sqrNum = (ld)sqrt(num);
	return sqrNum * sqrNum == num;
}

int solution() {
	int answer = -1;

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			// 모든 방향 탐색
			for (int dy = -n; dy <= n; dy++) {
				for (int dx = -m; dx <= m; dx++) {
					if (dy == 0 && dx == 0) continue;

					int y = r, x = c;
					ll num = 0;
					while (y >= 0 && y < n && x >= 0 && x < m) {
						num = num * 10 + (board[y][x] - '0');
						if (isSquare(num)) answer = max(answer, (int)num);

						y += dy;
						x += dx;
					}
				}
			}
		}
	}

	return answer;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> board[i];

	cout << solution() << '\n';
}
