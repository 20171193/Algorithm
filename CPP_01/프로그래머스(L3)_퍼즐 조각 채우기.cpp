#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define MaxPices 6

struct Piece
{
public:
	bool poses[MaxPices][MaxPices]{ false, };
	// 영역의 크기
	int size = 0;

	Piece() : size(0) {}
	Piece(const Piece& src) : size(0)
	{
		size = src.size;
		for (int i = 0; i < MaxPices; i++)
		{
			for (int j = 0; j < MaxPices; j++)
			{
				poses[i][j] = src.poses[i][j];
			}
		}
	}

	// 영역/조각 생성
	void MakePices(vector<pair<int, int>>& _poses)
	{
		size = _poses.size();
		for (pair<int, int> pos : _poses)
		{
			poses[pos.first][pos.second] = true;
		}
	}

	// 행렬 회전
	void Rotate()
	{
		bool tempPoses[MaxPices][MaxPices];
		copy(&poses[0][0], &poses[0][0] + MaxPices * MaxPices, &tempPoses[0][0]);
		for (int y = 0; y < MaxPices; y++)
		{
			for (int x = 0; x < MaxPices; x++)
			{
				poses[x][MaxPices - 1 - y] = tempPoses[y][x];
			}
		}
	}

	bool operator==(const Piece& pices) const
	{
		int rot = 4;
		Piece temp(pices);
		bool isCorrect = true;

		while (--rot)
		{
			for (int i = 0; i < MaxPices; i++)
			{
				for (int j = 0; j < MaxPices; j++)
				{
					if (temp.poses[i][j] != poses[i][j])
					{
						isCorrect = false;
						break;
					}
				}
				if (!isCorrect)
					break;
			}

			// 하나라도 성공 시 바로 삽입
			if (isCorrect)
				return true;
			// 행렬 회전
			temp.Rotate();
		}
		return false;
	}
};

bool cmp(const Piece& a, const Piece& b)
{
	return a.size < b.size;
}

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

vector<Piece> emptyAreas;
vector<Piece> puzzlePices;

bool BFS(bool target, int y, int x, vector<vector<int>>& _map, vector<vector<bool>>& visited, Piece& retArea)
{
	// 지나쳐온 경로할당
	vector<pair<int, int>> path;
	// BFS 탐색 큐
	queue<pair<int, int>> q;
	q.push({ y,x });
	visited[y][x] = true;

	// 시작지점을 원점으로 변경
	path.push_back({ y - y,x - x });


	while (q.size())
	{
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = dx[i] + cur.second;
			int ny = dy[i] + cur.first;

			// 예외처리
			if (nx < 0 || nx >= _map.size() || ny < 0 || ny >= _map.size())
				continue;
			if (visited[ny][nx])
				continue;
			if (_map[ny][nx] != target)
				continue;

			visited[ny][nx] = true;
			// 경로 할당
			path.push_back({ ny - y,nx - x });
			q.push({ ny,nx });
		}
	}

	// 퍼즐의 최대 크기 이상일 경우 
	if (path.size() > MaxPices)
		return false;
	else
	{
		retArea.MakePices(path);
		return true;
	}
}

void Search(bool target, vector<vector<int>>& vec)
{
	vector<vector<bool>> visited(vec.size(), vector<bool>(vec.size(), false));

	for (int y = 0; y < vec.size(); y++)
	{
		for (int x = 0; x < vec.size(); x++)
		{
			if (visited[y][x])
				continue;
			if (vec[y][x] != target)
				continue;

			Piece pices;
			if (BFS(target, y, x, vec, visited, pices))
			{
				target ? puzzlePices.push_back(pices) : emptyAreas.push_back(pices);
			}
		}
	}
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
	int answer = -1;

	Search(1, table);       // 퍼즐 할당 
	sort(puzzlePices.begin(), puzzlePices.end(), cmp); // 퍼즐 크기순으로 오름차정렬

	Search(0, game_board);  // 빈 공간 할당
	sort(emptyAreas.begin(), emptyAreas.end(), cmp);

	int areaIndex = 0;
	for (Piece& pices : puzzlePices)
	{
		for (int i = areaIndex; i < emptyAreas.size(); i++)
		{
			if (pices.size < emptyAreas[i].size)
				break;

			// 해당 구역을 채운경우
			if (pices == emptyAreas[i])
			{
				answer += pices.size;
				areaIndex++;
				break;
			}
			// 채우지 못한 경우
			else
				continue;
		}
	}

	return answer;
}

int main()
{
	vector<vector<int>> gboard =
	{
		{1,1,0,0,1,0},
		{0,0,1,0,1,0},
		{0,1,1,0,0,1},
		{1,1,0,1,1,1},
		{1,0,0,0,1,0},
		{0,1,1,1,0,0}
	};

	vector<vector<int>> table =
	{
		{1,0,0,1,1,0},
		{1,0,1,0,1,0},
		{0,1,1,0,1,1},
		{0,0,1,0,0,0},
		{1,1,0,1,1,0},
		{0,1,0,0,0,0}
	};

	solution(gboard, table);
}