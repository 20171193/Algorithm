// 백준 1725번 : 히스토그램
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int n, arr[100002];

int solution()
{
	int maxArea = 0;

	stack<int> st;
	st.push(0);	// sentienl

	//          1 2 3 4 5 10 7 8 9 10
	// pop 10 : 1 2 3 4 5 7 8 9 10
	for (int i = 1; i <= n + 1; i++)
	{
		while (!st.empty() && arr[st.top()] > arr[i])
		{
			int height = arr[st.top()];
			st.pop();

			int width = i - st.top() - 1;

			maxArea = max(maxArea, height * width);
		}
		st.push(i);
	}

	return maxArea;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	// output
	cout << solution() << '\n';
	return 0;
}