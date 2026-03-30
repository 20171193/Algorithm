#include <string>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int X = 0;
const int Y = 1;
const int INDEX = 2;


bool cmp(const vector<int>& a, const vector<int>& b)
{
    if (a[Y] == b[Y])
        return a[X] < b[X];
    return a[Y] > b[Y];
}
void insert(vector<pair<int, int>>& linkinfo, vector<vector<int>>& nodeinfo, int p, int c)
{
    if (nodeinfo[p][X] > nodeinfo[c][X])
    {
        if (linkinfo[p].first != -1)
            insert(linkinfo, nodeinfo, linkinfo[p].first, c);
        else
            linkinfo[p].first = c;
    }
    else
    {
        if (linkinfo[p].second != -1)
            insert(linkinfo, nodeinfo, linkinfo[p].second, c);
        else
            linkinfo[p].second = c;
    }
}

// 순회방식 개선 (재귀 -> 스택)
vector<int> preorder(const vector<vector<int>>& nodeinfo, const vector<pair<int, int>>& linkinfo, int root)
{
    vector<int> path;
    stack<int> st;
    st.push(root);

    while (!st.empty())
    {
        int cur = st.top();
        st.pop();

        path.push_back(nodeinfo[cur][INDEX]);

        if (linkinfo[cur].second != -1)
            st.push(linkinfo[cur].second);
        if (linkinfo[cur].first != -1)
            st.push(linkinfo[cur].first);
    }

    return path;
}
vector<int> postorder(const vector<vector<int>>& nodeinfo, const vector<pair<int, int>>& linkinfo, int root)
{
    vector<int> path;
    vector<bool> visited(nodeinfo.size(), false);
    stack<int> st;
    st.push(root);

    while (!st.empty())
    {
        int cur = st.top();

        if ((linkinfo[cur].first == -1 || visited[linkinfo[cur].first])
            && (linkinfo[cur].second == -1 || visited[linkinfo[cur].second]))
        {
            visited[cur] = true;
            path.push_back(nodeinfo[cur][INDEX]);
            st.pop();
        }
        else
        {
            if (linkinfo[cur].second != -1 && !visited[linkinfo[cur].second])
                st.push(linkinfo[cur].second);
            if (linkinfo[cur].first != -1 && !visited[linkinfo[cur].first])
                st.push(linkinfo[cur].first);
        }
    }

    return path;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer(2);

    for (int i = 0; i < nodeinfo.size(); i++)
        nodeinfo[i].push_back(i + 1);

    sort(nodeinfo.begin(), nodeinfo.end(), cmp);

    vector<pair<int, int>> linkinfo(nodeinfo.size(), { -1,-1 });
    for (int i = 1; i < nodeinfo.size(); i++)
        insert(linkinfo, nodeinfo, 0, i);

    answer[0] = preorder(nodeinfo, linkinfo, 0);
    answer[1] = postorder(nodeinfo, linkinfo, 0);

    return answer;
}


/* 개선 이전 : 재귀 방식 */
//#include <string>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//struct Node
//{
//    int num;
//    int x, y;
//    // index
//    int left = -1, right = -1;
//};
//bool cmp(const Node& a, const Node& b)
//{
//    if (a.y == b.y)
//        return a.x < b.x;
//    return a.y > b.y;
//}
//void preorder(const vector<Node>& nodes, int cur, vector<int>& path)
//{
//    path.push_back(nodes[cur].num);
//    if (nodes[cur].left != -1)
//        preorder(nodes, nodes[cur].left, path);
//    if (nodes[cur].right != -1)
//        preorder(nodes, nodes[cur].right, path);
//}
//void postorder(const vector<Node>& nodes, int cur, vector<int>& path)
//{
//    if (nodes[cur].left != -1)
//        postorder(nodes, nodes[cur].left, path);
//    if (nodes[cur].right != -1)
//        postorder(nodes, nodes[cur].right, path);
//    path.push_back(nodes[cur].num);
//}
//void InsertNode(vector<Node>& nodes, int parent, int child)
//{
//    if (nodes[parent].x > nodes[child].x)
//    {
//        if (nodes[parent].left == -1)
//            nodes[parent].left = child;
//        else
//            InsertNode(nodes, nodes[parent].left, child);
//    }
//    else
//    {
//        if (nodes[parent].right == -1)
//            nodes[parent].right = child;
//        else
//            InsertNode(nodes, nodes[parent].right, child);
//    }
//}
//vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
//    vector<vector<int>> answer(2);
//
//    vector<Node> nodes(nodeinfo.size());
//
//    for (int i = 0; i < nodeinfo.size(); i++)
//        nodes[i] = { i + 1, nodeinfo[i][0], nodeinfo[i][1] };
//
//    sort(nodes.begin(), nodes.end(), cmp);
//
//    // 노드 삽입 (루트는 0 : 좌표상 최상위)
//    for (int i = 1; i < nodes.size(); i++)
//        InsertNode(nodes, 0, i);
//
//    preorder(nodes, 0, answer[0]);
//    postorder(nodes, 0, answer[1]);
//
//    return answer;
//}
