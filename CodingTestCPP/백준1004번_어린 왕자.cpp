// 백준 1004번 : 어린 왕자
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// 1. 원의 방정식
// 2. 점을 포함하는 원의 개수
// 3. 시작점과 도착점을 모두 포함하는 원 고려
struct Circle {
	pair<int, int> center;
	int squareRadius;
};

int sqrDistance(const pair<int, int>& s, const pair<int, int>& e)
{
	return (e.first - s.first) * (e.first - s.first) + (e.second - s.second) * (e.second - s.second);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<int> answer;
	int t = 0;
	cin >> t;
	while (t--)
	{
		int n = 0;
		pair<int, int> start, end;
		cin >> start.first >> start.second >> end.first >> end.second;

		cin >> n;
		vector<Circle> circles;
		for (int i = 0; i < n; i++)
		{
			int x, y, r;
			cin >> x >> y >> r;
			circles.push_back({ {x,y}, r * r });	// square radius
		}

		int count = 0;
		for (auto circle : circles)
		{
			bool isInStart = sqrDistance(start, circle.center) < circle.squareRadius;
			bool isInEnd = sqrDistance(end, circle.center) < circle.squareRadius;

			if (isInStart != isInEnd)
				count++;
		}

		answer.push_back(count);
	}

	for (int ans : answer)
		cout << ans << '\n';

	return 0;
}