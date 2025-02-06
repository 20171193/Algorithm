#include <string>
#include <vector>
#include <queue>
using namespace std;

int visited[51];

// ���� �ٸ� �ܾ 2�� �̻� ���Ե� ��� ��ȯ�� �Ұ�.
bool CanChange(string& cur, string& target)
{
    int differ = 0;
    for (int i = 0; i < cur.size(); i++)
    {
        if (cur[i] != target[i])
            differ++;

        if (differ > 1)
            return false;
    }
    return true;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;

    int targetIndex = -1;
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == target)
            targetIndex = i;
    }
    // target �ܾ words �迭���� ������ ���� ��� (���� ���� ���)
    if (targetIndex == -1)
        return 0;

    queue<int> q;
    for (int i = 0; i < words.size(); i++)
    {
        // ���� ��ȯ�� ������ ��� �ܾ ť�� �߰�
        if (CanChange(begin, words[i]))
        {
            q.push(i);
            visited[i] = 1;
        }
    }

    // bfsŽ��
    while (q.size())
    {
        int curIndex = q.front();
        string& curWord = words[curIndex];
        q.pop();

        for (int i = 0; i < words.size(); i++)
        {
            // ���� Ž������ �ε����� ����
            if (i == curIndex) continue;
            // ��ȯ�� ������ �ܾ ����.
            if (!CanChange(curWord, words[i])) continue;
            // �̹� �湮�� ��� ����
            if (visited[i])
            {
                visited[i] = min(visited[i], visited[curIndex] + 1);
                continue;
            }

            q.push(i);
            visited[i] = visited[curIndex] + 1;
        }
    }

    return visited[targetIndex];
}