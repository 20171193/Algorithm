// 백준 2263번 : 트리의 순회
#include <iostream>
#include <vector>
using namespace std;

const int MAX_NODE = 100001;

int n, inOrder[100001], postOrder[100001], preOrder[100001], preIndex = 0;

// 후위순회 마지막 노드 - 루트노드
// 중위순회속 루트노드 찾아 서브트리 분할
// 반복

void solve(int inStart, int inEnd, int postStart, int postEnd)
{
	if (inStart > inEnd || postStart > postEnd)
		return;

	// 루트 방문
	int root = postOrder[postEnd];
	preOrder[preIndex++] = root;

	int rootIndex = -1;
	for (int i = inStart; i <= inEnd; i++)
	{
		if (inOrder[i] == root)
		{
			rootIndex = i;
			break;
		}
	}

	if (rootIndex == -1)
		return;


	// 왼쪽 서브트리 크기
	int leftSize = rootIndex - inStart;

	// 왼쪽 방문
	solve(inStart, rootIndex - 1, postStart, postStart + leftSize - 1);
	// 오른쪽 방문
	solve(rootIndex + 1, inEnd, postStart + leftSize, postEnd - 1);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> inOrder[i];
	for (int i = 0; i < n; i++)
		cin >> postOrder[i];

	solve(0, n - 1, 0, n - 1);

	// output
	for (int i = 0; i < n; i++)
		cout << preOrder[i] << ' ';

	return 0;
}


