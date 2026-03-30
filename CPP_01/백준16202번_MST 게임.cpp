// 백준16202번 MST 게임
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int n, m, k, arr[1001];


class UnionFindSplit
{
public:
	UnionFindSplit() {}
	// 루트노드 탐색
	int Find(int a, vector<int>& root)
	{
		if (root[a] != a)
			root[a] = Find(root[a], root);
		return root[a];
	}
	// 두 트리를 연결
	void Union(int a, int b, vector<int>& root, vector<int>& depth)
	{
		int rootA = Find(a, root);
		int rootB = Find(b, root);
		// 이미 연결되어있는 경우
		if (rootA == rootB) return;

		// 트리 깊이에 따라 연결
		if (depth[rootA] > depth[rootB])
			root[rootB] = rootA;
		else if (depth[rootA] < depth[rootB])
			root[rootA] = rootB;
		// 깊이가 동일한 경우
		else
		{
			root[rootB] = rootA;
			depth[rootA]++;	// 깊이를 1 증가
		}
	}
	// 연결된 트리를 두 트리로 분할
	void Split(int a, int b, vector<int>& root, vector<int>& depth)
	{
		int rootA = Find(a, root);
		int rootB = Find(b, root);

		// 이미 분할된 트리일 경우
		if (rootA != rootB) return;

		root[b] = b;
	}
	// 두 트리가 연결되어있는지 확인
	bool IsLinked(int a, int b, vector<int>& root)
	{
		return Find(a, root) == Find(b, root);
	}
};
class Graph
{
private:
	map<int, pair<int, int>> totalEdges;	// 중복없는 간선
	int nodes;
	int mstValue;		// MST 가중치 총합
	int minValueEdge;	// MST를 구성하는 간선 중 가중치가 가장 작은 간선
	vector<int> root;	// 루트 노드
	vector<int> depth;	// 트리의 깊이
	UnionFindSplit ufs;
public:
	Graph(int node) : nodes(node), ufs()
	{
		root.push_back(-1);
		depth.push_back(-1);
		for (int i = 1; i <= node; i++)
		{
			root.push_back(i);	// 최초 루트노드 세팅
			depth.push_back(0);	// 깊이 세팅
		}
	}
	void AddEdge(int a, int b, int value)
	{
		// 중복된 간선은 주어지지 않음.
		// 가중치는 오름차순
		totalEdges.insert({ value, {a,b} });
	}
	void RemoveEdge()
	{
		// 현재 구성된 최소 신장트리에서 가장 가중치가 가장 낮은 간선 제거
		if (totalEdges.find(minValueEdge) != totalEdges.end())
		{
			auto& edge = totalEdges[minValueEdge];
			// 최소 신장트리 가중치 갱신
			mstValue -= minValueEdge;
			// 트리 분할
			ufs.Split(edge.first, edge.second, root, depth);
			// 간선 제거
			totalEdges.erase(minValueEdge);	// 가중치로만 확인 (가중치는 중복이 없음)
			// MST 초기화
			ClearMST();
		}
	}
	// 최소 신장트리를 구성한 뒤 가중치 반환
	bool MakeMST(int& retValue)
	{
		minValueEdge = -1;	// 최대 가중치를 가지는 간선 초기화
		mstValue = 0;		// MST 비용 초기화
		int edgeCount = 0;	// MST가 구성되었다면 간선의 개수는 V-1
		for (auto iter = totalEdges.begin(); iter != totalEdges.end(); iter++)
		{
			pair<int, int> edge = (*iter).second;
			int value = (*iter).first;
			// 연결되어있지 않다면
			if (!ufs.IsLinked(edge.first, edge.second, root))
			{
				// 오름차순으로 정렬된 간선에서 처음으로 연결된 간선이 최소 가중치의 간선
				if (minValueEdge == -1)
					minValueEdge = value;
				mstValue += value;
				edgeCount++;
				// 간선을 통한 연결
				ufs.Union(edge.first, edge.second, root, depth);
			}
		}

		// MST를 구성할 수 없는 경우
		if (edgeCount < nodes - 1)
			return false;
		else
		{
			retValue = mstValue;
			return true;
		}
	}
	// 최소신장트리 초기화
	void ClearMST()
	{
		for (int i = 1; i <= nodes; i++)
		{
			root[i] = i;
			depth[i] = 0;
		}
	}
};

int main()
{
	cin >> n >> m >> k;
	Graph graph(n);
	for (int i = 1; i <= m; i++)
	{
		int a, b;
		cin >> a >> b;
		graph.AddEdge(a, b, i);
	}

	while (k--)
	{
		int value = 0;
		if (graph.MakeMST(value))
			cout << value << ' ';
		else
		{
			// 더이상 MST를 구성할 수 없는 경우
			// 게임 종료
			do {
				cout << 0 << ' ';
			} while (k--);

			break;
		}
		graph.RemoveEdge();
	}
	return 0;
}