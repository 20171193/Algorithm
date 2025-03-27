#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
    int num;
    int x, y;
    // index
    int left = -1, right = -1;
};

bool cmp(const Node& a, const Node& b)
{
    if (a.y == b.y)
        return a.x < b.x;
    return a.y > b.y;
}

void preorder(const vector<Node>& nodes, int cur, vector<int>& path)
{
    path.push_back(nodes[cur].num);
    if (nodes[cur].left != -1)
        preorder(nodes, nodes[cur].left, path);
    if (nodes[cur].right != -1)
        preorder(nodes, nodes[cur].right, path);
}
void postorder(const vector<Node>& nodes, int cur, vector<int>& path)
{
    if (nodes[cur].left != -1)
        postorder(nodes, nodes[cur].left, path);
    if (nodes[cur].right != -1)
        postorder(nodes, nodes[cur].right, path);
    path.push_back(nodes[cur].num);
}

void InsertNode(vector<Node>& nodes, int parent, int child)
{
    if (nodes[parent].x > nodes[child].x)
    {
        if (nodes[parent].left == -1)
            nodes[parent].left = child;
        else
            InsertNode(nodes, nodes[parent].left, child);
    }
    else
    {
        if (nodes[parent].right == -1)
            nodes[parent].right = child;
        else
            InsertNode(nodes, nodes[parent].right, child);
    }
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer(2);

    vector<Node> nodes(nodeinfo.size());

    for (int i = 0; i < nodeinfo.size(); i++)
        nodes[i] = { i + 1, nodeinfo[i][0], nodeinfo[i][1] };

    sort(nodes.begin(), nodes.end(), cmp);

    // 노드 삽입 (루트는 0 : 좌표상 최상위)
    for (int i = 1; i < nodes.size(); i++)
        InsertNode(nodes, 0, i);

    preorder(nodes, 0, answer[0]);
    postorder(nodes, 0, answer[1]);

    return answer;
}