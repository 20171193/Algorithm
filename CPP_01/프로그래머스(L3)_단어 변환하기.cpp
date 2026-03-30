#include <string>
#include <vector>
#include <queue>
using namespace std;

int visited[51];

// 서로 다른 단어가 2개 이상 포함된 경우 변환이 불가.
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
    // target 단어가 words 배열내에 속하지 않은 경우 (답이 없는 경우)
    if (targetIndex == -1)
        return 0;

    queue<int> q;
    for (int i = 0; i < words.size(); i++)
    {
        // 최초 변환이 가능한 모든 단어를 큐에 추가
        if (CanChange(begin, words[i]))
        {
            q.push(i);
            visited[i] = 1;
        }
    }

    // bfs탐색
    while (q.size())
    {
        int curIndex = q.front();
        string& curWord = words[curIndex];
        q.pop();

        for (int i = 0; i < words.size(); i++)
        {
            // 현재 탐색중인 인덱스를 제외
            if (i == curIndex) continue;
            // 변환이 가능한 단어에 한함.
            if (!CanChange(curWord, words[i])) continue;
            // 이미 방문한 경우 갱신
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