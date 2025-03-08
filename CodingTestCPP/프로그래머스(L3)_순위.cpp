#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;

    // �̱� �������� �Ҵ�
    vector<vector<int>> childs(n + 1);
    // �� �������� �Ҵ�
    vector<vector<int>> parents(n + 1);

    for (const vector<int>& res : results)
    {
        childs[res[0]].push_back(res[1]);
        parents[res[1]].push_back(res[0]);
    }

    queue<pair<int, bool>> q;
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        int visitCount = 0;

        // ��� �������� bfs Ž���� �����ϸ� �̱� ������ true, �� ������ false�� ��ŷ
        // ���� ��ŷ�� ������ Ž���� ����.
        //  ���� : (1,2) (1,3)�� ��� 1�� ������ 2, 3 ������ Ž���� �� ������
        //         2, 3������ ���θ� Ž���� �� ����. (1�� ������ Ž������)  
        q.push({ i,true });
        q.push({ i,false });
        visited[i] = true;

        while (!q.empty())
        {
            int curNode = q.front().first;
            bool curType = q.front().second;
            q.pop();

            for (int next : (curType ? parents[curNode] : childs[curNode]))
            {
                if (visited[next])
                    continue;

                visitCount++;
                visited[next] = true;
                q.push({ next, curType });
            }
        }

        if (visitCount == n - 1)
            answer++;

        fill(visited.begin(), visited.end(), false);
    }

    return answer;
}
