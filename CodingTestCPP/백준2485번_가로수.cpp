// ���� 2485�� : ���μ�
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int INF = 1000000001;

int n, minGap = INF;
vector<int> gaps;

int GetGCD(int a, int b)
{
	while (b > 0)
	{
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int solve()
{
	int answer = 0;

	// ���ݵ��� �ִ� �����
	int gcd = gaps[0];
	for (int i = 1; i < gaps.size(); i++)
		gcd = GetGCD(gcd, gaps[i]);

	for (int gap : gaps)
		answer += gap / gcd - 1;

	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int prev = 0, cur = 0;
	cin >> prev;
	for (int i = 1; i < n; i++)
	{
		cin >> cur;
		gaps.push_back(cur - prev);
		prev = cur;
	}

	cout << solve() << '\n';
	return 0;
}