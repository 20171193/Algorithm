// 백준 1941번 : 소문난 칠공주 (https://www.acmicpc.net/problem/1941)
// DFS(완탐)+BFS(연결성 체크)
// 추가)BFS로 효율성 늘리기
#include <iostream>
#include <string>
#include <queue>
#include <cmath>
using namespace std;

string arr[5];
int answer = 0;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

// BFS 연결성 체크
bool isConnected(int bit)
{
	queue<pair<int, int>> q;
	int visited = 0;
	for (int i = 0; i < 25; i++)
	{
		if (bit & (1 << i))
		{
			q.push({ i / 5, i % 5 });
			visited |= (1 << i);

			while (!q.empty())
			{
				auto cur = q.front();
				q.pop();

				for (int d = 0; d < 4; d++)
				{
					int ny = dy[d] + cur.first;
					int nx = dx[d] + cur.second;
					if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
					int nBit = 1 << (ny * 5 + nx);
					if (!(bit & nBit)) continue;
					if (visited & nBit) continue;
					q.push({ ny,nx });
					visited |= nBit;
				}
			}

			break;
		}
	}

	return visited == bit;
}

// DFS 완전탐색 (bit 방문체크)
void solution(int idx, int bit, int totalCount, int sCount)
{
	if (totalCount == 7)
	{
		if (sCount >= 4 && isConnected(bit))
			answer++;
		return;
	}
	if (idx >= 25) return;

	// 현재 인덱스 선택 o
	solution(idx + 1, bit | (1 << idx), totalCount + 1, sCount + (arr[idx / 5][idx % 5] == 'S'));
	// 현재 인덱스 선택 x
	solution(idx + 1, bit, totalCount, sCount);
}

int main()
{
	for (int i = 0; i < 5; i++)
		cin >> arr[i];

	solution(0, 0, 0, 0);

	cout << answer << '\n';
	return 0;
}