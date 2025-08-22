// ���α׷��ӽ�(L3) : ���Ӱ� ����׷���
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// ���� : ����Ŭ (n, n)
// ���� : �ܹ��� (n, n-1)
// 8�� : ������ 2���� ���� ���� (2n+1, 2n+2)

// ���
// : 1. ������ ���� ��ȣ
// : 2. ���� �������� ���� �׷����� ��
// : 3. ���� �׷��� �� 
// : 4. 8�� �׷��� ��

// ���� : 1 - 2 - 3 - 1 (����Ŭ�� ����)
// ���� : 1 - 2 - 3
// 8�� : 1 - 2 - 3 - 4 - 5 - 3 - 1 (Ž�� ���� ����Ŭ �߰�)
// ������ �� : �ΰ� �̻��� ������ ���� && ������ ���� = 0

enum OUTPUT_INDEX {
    CREATE = 0,
    DONUT = 1,
    STICK = 2,
    EIGHT = 3
};

// dfs���
bool IsDonutGraph(int curNode, const vector<vector<int>>& graph, vector<bool>& visited)
{
    if (visited[curNode])
        return true;

    visited[curNode] = true;

    // ����� ������ ���� ��� (���� �׷���)
    if (graph[curNode].size() == 0)
        return false;

    return IsDonutGraph(graph[curNode][0], graph, visited);
}

vector<int> solution(vector<vector<int>> edges) {
    vector<int> answer(4);

    int size = -1;
    for (int i = 0; i < edges.size(); i++)
        size = max({ size, edges[i][0], edges[i][1] });

    // �׷��� ����
    // ������ �� ã�� 
    vector<vector<int>> graph(size + 1); //1-based
    vector<bool> isIn(size + 1); // ���� ������ ����Ǿ��ٸ� true
    vector<int> candi;  // ���� ������ 2�� �̻��� ����
    for (const vector<int>& edge : edges)
    {
        graph[edge[0]].push_back(edge[1]);
        isIn[edge[1]] = true;

        if (graph[edge[0]].size() > 1)
            candi.push_back(edge[0]);
    }

    vector<bool> visited(size + 1, false);
    // 1. ���� ������ �ΰ� �̻��� ������ �ĺ��� ��� 
    int startNode = -1;
    for (int node : candi)
    {
        //  2-1. ���� ������ ������ 8�� �׷����� ��ȯ���
        //       : �ش� ���� ����� ���� �湮üũ �� 8�� �׷��� ����+1
        if (isIn[node])
        {
            visited[node] = true;
            for (int linkedNode : graph[node])
                IsDonutGraph(linkedNode, graph, visited);

            answer[OUTPUT_INDEX::EIGHT]++;
        }
        //  2-2. ���ٸ� ������ ��
        //       : ������ ���� ����� �� �� �湮���� ���� �������� �׷��� Ȯ��
        else
        {
            startNode = node;
            answer[OUTPUT_INDEX::CREATE] = startNode;
        }
    }

    visited[startNode] = true;
    for (int next : graph[startNode])
    {
        if (visited[next]) continue;
        if (IsDonutGraph(next, graph, visited))
            answer[OUTPUT_INDEX::DONUT]++;
        else
            answer[OUTPUT_INDEX::STICK]++;
    }

    return answer;
}