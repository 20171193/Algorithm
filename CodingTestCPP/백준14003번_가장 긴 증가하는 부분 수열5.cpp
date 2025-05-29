// 백준 14003번 : 가장 긴 증가하는 부분 수열 5
// LIS + 역추적
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, arr[1000001];

vector<int> solve()
{
	vector<int> lis,	// lis값
		lisIdx,			// lis에 속한 실제 인덱스
		pos(n),			// lis위치
		prev(n, -1);	// 역추적

	// LIS, 역추적 경로 할당
	for (int i = 0; i < n; i++)
	{
		int num = arr[i];
		int idx = lower_bound(lis.begin(), lis.end(), num) - lis.begin();

		if (idx == lis.size())
		{
			lis.push_back(num);
			lisIdx.push_back(i);
		}
		else
		{
			lis[idx] = num;
			lisIdx[idx] = i;
		}

		pos[i] = idx;

		if (idx > 0)
			prev[i] = lisIdx[idx - 1];
	}

	// 역추적
	vector<int> result;
	int curIdx = lisIdx.back();
	while (curIdx != -1)
	{
		result.push_back(arr[curIdx]);
		curIdx = prev[curIdx];
	}

	reverse(result.begin(), result.end());
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	vector<int> answerArr = solve();
	cout << answerArr.size() << '\n';

	string answer = "";
	for (int ans : answerArr)
		answer += to_string(ans) + ' ';

	cout << answer << '\n';
	return 0;
}