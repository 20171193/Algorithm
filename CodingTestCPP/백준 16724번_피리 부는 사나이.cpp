// ���� 16724�� : �Ǹ� �δ� �糪��
// ����Ŭ ����
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m;
bool visited[1001][1001];
string dir[1001];

int GetSafeZoneCount()
{
	int ret = 0;

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (visited[y][x]) continue;

			int ny = y, nx = x;
			while (!visited[ny][nx])
			{
				visited[ny][nx] = true;

				switch (dir[ny][nx])
				{
				case 'U': ny--; break;
				case 'D': ny++; break;
				case 'R': nx++; break;
				case 'L': nx--; break;
				default: break;
				}
			}

			ret++;
		}
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> dir[i];

	cout << GetSafeZoneCount() << '\n';
	return 0;
}