// ���� 2263�� : Ʈ���� ��ȸ
#include <iostream>
#include <vector>
using namespace std;

const int MAX_NODE = 100001;

int n, inOrder[100001], postOrder[100001], preOrder[100001], preIndex = 0;

// ������ȸ ������ ��� - ��Ʈ���
// ������ȸ�� ��Ʈ��� ã�� ����Ʈ�� ����
// �ݺ�

void solve(int inStart, int inEnd, int postStart, int postEnd)
{
	if (inStart > inEnd || postStart > postEnd)
		return;

	// ��Ʈ �湮
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


	// ���� ����Ʈ�� ũ��
	int leftSize = rootIndex - inStart;

	// ���� �湮
	solve(inStart, rootIndex - 1, postStart, postStart + leftSize - 1);
	// ������ �湮
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


