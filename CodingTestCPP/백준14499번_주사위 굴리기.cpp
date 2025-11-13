// 백준14499번 : 주사위 굴리기
// **전/후방으로 이동 시(회전 시) 좌/우측은 영향없음.(좌/우측도 마찬가지)
// **회전으로 인한 swap에 규칙이 존재.
#include <iostream>
using namespace std;

constexpr int TOP = 0, BOT = 5;

int dx[5] = { 0, 1, -1, 0, 0 }
, dy[5] = { 0, 0, 0, -1, 1 }
, dice[6] = { 0,0,0,0,0,0 };

int n, m, k, order[1001], arr[21][21];
pair<int, int> dicePos;

void solution()
{
	for (int i = 0; i < k; i++)
	{
		int dir = order[i];

		// 좌표 이동
		int ny = dicePos.first + dy[dir];
		int nx = dicePos.second + dx[dir];
		if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
		dicePos = { ny,nx };

		// 육면체 회전
		int oppDir = dir % 2 == 0
			? dir - 1 : dir + 1;	// 반대 면
		// swap(회전)
		int botTemp = dice[dir];
		dice[dir] = dice[TOP];
		dice[TOP] = dice[oppDir];
		dice[oppDir] = dice[BOT];

		// 마킹(복사)
		if (arr[ny][nx] == 0)
			arr[ny][nx] = dice[BOT] = botTemp;
		else
		{
			dice[BOT] = arr[ny][nx];
			arr[ny][nx] = 0;
		}

		cout << dice[TOP] << '\n';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> dicePos.first >> dicePos.second >> k;

	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++)
			cin >> arr[y][x];

	for (int i = 0; i < k; i++)
		cin >> order[i];

	solution();
	return 0;
}