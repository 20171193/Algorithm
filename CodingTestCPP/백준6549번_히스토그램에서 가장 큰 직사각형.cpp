// 백준 6549번 - 히스토그램에서 가장 큰 직사각형
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

typedef long long ll;
int n;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (1)
	{
		cin >> n;
		if (n == 0)
			break;

		vector<int> heights(n);
		stack<int> st;
		ll maxArea = 0;

		for (int i = 0; i < n; i++)
		{
			cin >> heights[i];
			// 높이가 갱신될 때마다 계산
			while (!st.empty() && heights[st.top()] > heights[i])
			{
				int h = heights[st.top()];
				st.pop();

				int w = st.empty() ? i : i - st.top() - 1;
				maxArea = max(maxArea, (ll)h * w);
			}
			st.push(i);
		}

		while (!st.empty())
		{
			int h = heights[st.top()];
			st.pop();
			int w = st.empty() ? n : n - st.top() - 1;
			maxArea = max(maxArea, (ll)h * w);
		}

		cout << maxArea << '\n';
	}


	return 0;
}