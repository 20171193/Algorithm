#include <iostream>
#include <vector>
using namespace std;

int n, ret, arr[17][17];

struct Pipe
{
	int x;
	int y;
	int shape;

	Pipe(int _y, int _x, int _shape)
	{
		y = _y;
		x = _x;
		shape = _shape;
	}
};
bool CheckBound(Pipe p)
{
	if (p.y < 1 || p.y > n || p.x < 1 || p.x > n)
		return false;
	if (arr[p.y][p.x])
		return false;
	if (p.shape == 2 && (arr[p.y - 1][p.x] || arr[p.y][p.x - 1]))
		return false;
	return true;
}
vector<Pipe> NextPipe(Pipe cur)
{
	if (cur.shape == 0)
		return { Pipe(cur.y, cur.x + 1, 0), Pipe(cur.y + 1, cur.x + 1, 2) };
	else if (cur.shape == 1)
		return { Pipe(cur.y + 1, cur.x, 1), Pipe(cur.y + 1, cur.x + 1, 2) };
	else
		return { Pipe(cur.y, cur.x + 1, 0), Pipe(cur.y + 1, cur.x, 1), Pipe(cur.y + 1, cur.x + 1, 2) };

}
void DFS(Pipe cur)
{
	if (cur.y == n && cur.x == n)
	{
		ret++;
		return;
	}

	vector<Pipe> nexts = NextPipe(cur);
	for (auto iter = nexts.begin(); iter != nexts.end(); iter++)
	{
		if (CheckBound(*iter))
			DFS(*iter);
	}
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> arr[i][j];

	DFS(Pipe(1, 2, 0));

	cout << ret << '\n';
	return 0;
}