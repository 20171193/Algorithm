// 백준16235번 : 나무 재테크 (https://www.acmicpc.net/problem/16235)
// 조건 체크
// 1. 각 칸마다 여러 개의 나무가 있을 수 있음.
// 2. 최초 양분은 5씩
// 3. 양분을 못 먹는 경우 바로 죽음
// 4. 칸 마다 나이가 적은 나무부터 양분을 먹음
// 5. 사계절
//  5-1. 봄 : 자신의 나이만큼 양분을 먹고, 나이 1증가
//  5-2. 여름 : 봄에 죽은 나무가 양분으로 변함. floor(나이/2) 
//  5-3. 가을 : 나이가 5배수인 나무들이 번식(인접한 8칸)
//  5-4. 겨울 : 땅에 양분 추가

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

int dx[8] = { -1,-1,-1,0,0,1,1,1 }
, dy[8] = { -1,0,1,-1,1,-1,0,1 };

struct Tree
{
	int _y, _x, _age;
	Tree() : _y(0), _x(0), _age(0) {}
	Tree(int y, int x, int age) : _y(y), _x(x), _age(age) {}
};

int solution(int n, int m, int k, vector<vector<int>>& area, const vector<vector<int>>& adds, vector<Tree>& trees)
{
	int count = 0;

	// 최초 한번 정렬(이후 번식 시 push_front)
	// 어차피 새로 생성되는 나무는 나이가 1
	sort(trees.begin(), trees.end(), [](const Tree& a, const Tree& b) {
		return a._age < b._age;
		});

	vector<vector<deque<int>>> treeArea(n + 1, vector<deque<int>>(n + 1));
	for (Tree t : trees)
	{
		treeArea[t._y][t._x].push_back(t._age);
		count++;
	}

	// 새로 생성되는 나무 개수(1차원 접근)
	vector<int> pendingAdds(n * n + 1);
	while (k--)
	{
		// 봄 : 자신의 나이만큼 양분을 먹고, 나이 1증가
		for (int y = 1; y <= n; y++)
		{
			for (int x = 1; x <= n; x++)
			{
				deque<int>& dq = treeArea[y][x];
				if (dq.empty()) continue;

				// 죽은 나무 카운팅
				int deathCount = 0;
				for (auto iter = dq.begin(); iter != dq.end(); iter++)
				{
					int& curAge = *iter;
					if (area[y][x] >= curAge)
					{
						area[y][x] -= curAge++;
						if (curAge % 5 == 0)
						{
							for (int d = 0; d < 8; d++)
							{
								int nx = x + dx[d], ny = y + dy[d];
								if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
								int index = (ny - 1) * n + nx;
								pendingAdds[index]++;
							}
						}
					}
					else
						deathCount++;
				}

				count -= deathCount;
				// 여름 : 봄에 죽은 나무가 양분으로 변함. floor(나이/2) 
				while (deathCount--)
				{
					// 죽은 나무 개수만큼 뒤에서 탐색
					area[y][x] += dq.back() / 2;
					dq.pop_back();
				}
			}
		}

		for (int y = 1; y <= n; y++)
		{
			for (int x = 1; x <= n; x++)
			{
				// 가을 : 추가된 나무 처리
				int index = (y - 1) * n + x;
				count += pendingAdds[index];
				while (pendingAdds[index]--)
					treeArea[y][x].push_front(1);
				pendingAdds[index] = 0;

				// 겨울 : 양분 추가
				area[y][x] += adds[y][x];
			}
		}
	}

	return count;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<int>> area(n + 1, vector<int>(n + 1, 5));

	vector<vector<int>> adds(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> adds[i][j];

	vector<Tree> trees(m);
	for (Tree& t : trees)
		cin >> t._y >> t._x >> t._age;

	cout << solution(n, m, k, area, adds, trees) << '\n';
	return 0;
}