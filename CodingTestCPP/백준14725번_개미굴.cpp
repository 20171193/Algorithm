// 백준 14725번 : 개미굴
#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Node
{
	string _name;
	int _depth;
	map<string, Node*, less<string>> childs;
	Node(string name, int depth) : _name(name), _depth(depth) {}
};

void DFS(const Node* node)
{
	if (node->_depth >= 0)
	{
		string depthStr = "";
		for (int d = 1; d <= node->_depth; d++)
			depthStr += "--";

		cout << depthStr + node->_name << '\n';
	}

	for (auto iter = node->childs.begin(); iter != node->childs.end(); iter++)
		DFS((*iter).second);
}

int main()
{
	ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	cout.tie(NULL);

	Node* root = new Node("", -1);

	int n = 0;
	std::cin >> n;

	// 트리 생성
	for (int i = 0; i < n; i++)
	{
		int count = 0;
		std::cin >> count;

		Node* cur = root;
		for (int d = 0; d < count; d++)
		{
			string name = "";
			std::cin >> name;

			if (cur->childs.find(name) == cur->childs.end())
			{
				Node* next = new Node(name, d);
				cur->childs.insert({ name, next });
			}
			cur = cur->childs[name];
		}
	}

	// 트리 순회
	DFS(root);
	return 0;
}