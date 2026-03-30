// 백준 17143번 : 낚시왕
#include <iostream>
#include <vector>
using namespace std;

int r, c, m;

class Shark;
Shark* sharks[10001];
vector<Shark*> vec;

int dx[5] = { 0, 0, 0, 1, -1 };
int dy[5] = { 0, -1, 1, 0, 0 };

class Shark {
private:
	bool _disable = false;
	void Turn()
	{
		if (_d == 1) _d = 2;
		else if (_d == 2) _d = 1;
		else if (_d == 3) _d = 4;
		else if (_d == 4) _d = 3;
	}
public:
	int _y, _x, _s, _d, _z, _i;
	int _moveCount = 0;
	Shark(int y, int x, int s, int d, int z, int i) : _y(y), _x(x), _s(s), _d(d), _z(z), _i(i) {}
	bool IsDisable() { return _disable; }
	void Disable() { _disable = true; }
	void Move()
	{
		if (_disable) return;

		sharks[_i] = nullptr;

		int moveS = _d <= 2 ? _s % ((r - 1) * 2) : _s % ((c - 1) * 2);
		// 3 5 9 11 15
		while (moveS > 0)
		{
			if ((_d == 1 && _y == 0) || (_d == 2 && _y == r - 1)
				|| (_d == 3 && _x == c - 1) || (_d == 4 && _x == 0))
				Turn();

			_y += dy[_d];
			_x += dx[_d];
			moveS--;
		}

		_moveCount++;

		_i = _y * c + _x;
		// 상어가 이미 존재하는 경우
		if (sharks[_i] != nullptr && !sharks[_i]->IsDisable())
		{
			if (sharks[_i]->_moveCount < _moveCount)
				sharks[_i]->Move();

			if (sharks[_i] != nullptr)
			{
				if (sharks[_i]->_z > _z)
				{
					Disable();
					return;
				}
				else
					sharks[_i]->Disable();
			}
		}
		sharks[_i] = this;
	}
};



int solution()
{
	int result = 0;

	int moveCount = 0;
	for (int x = 0; x < c; x++)
	{
		int index = 0;
		for (int y = 0; y < r; y++)
		{
			index = y * c + x;
			if (sharks[index] == nullptr || sharks[index]->IsDisable())
				continue;

			result += sharks[index]->_z;
			sharks[index]->Disable();
			sharks[index] = nullptr;
			break;
		}

		moveCount++;
		for (int i = 0; i < vec.size(); i++)
		{
			if (!vec[i]->IsDisable() && vec[i]->_moveCount < moveCount)
				vec[i]->Move();
		}
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> r >> c >> m;
	for (int i = 0; i < m; i++)
	{
		int y, x, s, d, z;
		cin >> y >> x >> s >> d >> z;
		int index = (y - 1) * c + (x - 1);
		Shark* inst = new Shark(y - 1, x - 1, s, d, z, index);
		sharks[index] = inst;
		vec.push_back(inst);
	}

	cout << solution() << '\n';

	for (int i = 0; i < vec.size(); i++)
		delete vec[i];

	return 0;
}