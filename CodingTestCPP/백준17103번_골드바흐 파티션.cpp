// 백준 17103번 : 골드바흐 파티션
#include <iostream>
#include <vector>
using namespace std;

constexpr int INF = 1000000;

// 에라토스테네스의 체
vector<bool> InitPrime()
{
	vector<bool> isPrime(INF + 1, true);

	for (int i = 2; i * i <= INF; ++i)
	{
		if (isPrime[i])
		{
			for (int j = i * i; j <= INF; j += i)
				isPrime[j] = false;
		}
	}

	return isPrime;
}

vector<int> solution(const vector<int>& inputs)
{
	vector<int> result(inputs.size());
	vector<bool> isPrime = InitPrime();

	for (int i = 0; i < inputs.size(); i++)
	{
		int curNum = inputs[i], count = 0, oppNum = 0;
		for (int p = 2; p <= curNum / 2; p++)
		{
			if (!isPrime[p]) continue;
			oppNum = curNum - p;
			if (!isPrime[oppNum]) continue;

			count++;
		}

		result[i] = count;
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// input
	int t = 0;
	cin >> t;

	vector<int> inputs(t);
	for (int i = 0; i < t; i++)
		cin >> inputs[i];

	// output
	for (int ans : solution(inputs))
		cout << ans << '\n';

	return 0;
}