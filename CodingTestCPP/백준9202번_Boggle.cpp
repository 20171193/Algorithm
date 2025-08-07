// 백준 9202번 : Boggle
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <memory>
using namespace std;

int w, b;
string words[300001], boards[31][4];

int score[9] = { 0,0,0,1,1,2,3,5,11 };

// 8방향
int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { 1,0,-1,1,-1,1,0,-1 };

int GetBit(int y, int x)
{
	return 1 << (y * 4 + x + 1);
}

struct Node {
	string _target, _current;
	int _y, _x, _visited;
	Node() : _y(-1), _x(-1), _visited(0), _target(""), _current("") {}
	Node(int y, int x, int visited, string target, string current) : _y(y), _x(x), _target(target), _visited(visited), _current(current) {}

	Node Move(int y, int x, int nVisited, char c)
	{
		return { y, x, _visited | nVisited, _target,  _current + c };
	}
	int GetScore()
	{
		return score[_target.size()];
	}
	bool isArrived()
	{
		return _target.size() == _current.size() && _target.back() == _current.back();
	}
	bool CheckPath(char c)
	{
		if (_current.size() < _target.size() && _current + c == _target.substr(0, _current.size() + 1))
			return true;
		return false;
	}
};

bool dfs(Node curNode, const string* curBoard)
{
	if (curNode.isArrived())
		return true;

	for (int d = 0; d < 8; d++)
	{
		int ny = dy[d] + curNode._y;
		int nx = dx[d] + curNode._x;
		if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;	// 범위체크
		int nVisited = GetBit(ny, nx);
		if (curNode._visited & nVisited) continue;	// 방문체크
		char nChar = curBoard[ny][nx];
		if (!curNode.CheckPath(nChar)) continue;	// 경로체크

		Node next = curNode.Move(ny, nx, nVisited, curBoard[ny][nx]);
		if (dfs(next, curBoard))
			return true;
	}
	return false;
}

string solution(int boardNum)
{
	string* curBoard = boards[boardNum];

	string result = "";

	vector<bool> checked(w, false);
	queue<Node> q;
	int getScore = 0, findCount = 0;
	string longestWord = "";
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int wi = 0; wi < w; wi++)
			{
				if (checked[wi]) continue;
				string curWord = words[wi];

				if (curBoard[y][x] == curWord[0])
				{
					Node node(y, x, GetBit(y, x), curWord, curWord.substr(0, 1));
					if (dfs(node, boards[boardNum]))
					{
						checked[wi] = true;
						getScore += node.GetScore();
						if (longestWord.size() < curWord.size()
							|| (longestWord.size() == curWord.size() && longestWord > curWord))
							longestWord = curWord;
						findCount++;
					}
				}
			}
		}
	}

	result = to_string(getScore)
		+ ' ' + longestWord + ' '
		+ to_string(findCount);
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input
	cin >> w;
	for (int i = 0; i < w; i++)
		cin >> words[i];

	cin >> b;
	for (int i = 0; i < b; i++)
		for (int j = 0; j < 4; j++)
			cin >> boards[i][j];

	// solve
	vector<string> answer;
	for (int i = 0; i < b; i++)
		answer.push_back(solution(i));

	// output
	for (const string& ans : answer)
		cout << ans << '\n';
	return 0;
}