#include <string>
#include <vector>
using namespace std;

void dfs(int idx, int mask, vector<string>& user_id, vector<int>& candidates, bool* used, int& answer)
{
    if (idx >= candidates.size())
    {
        if (!used[mask])
        {
            used[mask] = true;
            answer++;
        }
        return;
    }

    int cur = candidates[idx];
    for (int i = 0; i < user_id.size(); i++)
    {
        int next = 1 << i;
        if (!(cur & next) || (mask & next))
            continue;

        dfs(idx + 1, mask | next, user_id, candidates, used, answer);
    }
}

// 각 banned_id에 매칭되는 후보군 비트마스킹
int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;

    vector<int> candidates;
    // 2^1~8
    bool used[257] = { false, };

    for (int i = 0; i < banned_id.size(); i++)
    {
        int mask = 0;
        for (int j = 0; j < user_id.size(); j++)
        {
            if (user_id[j].size() != banned_id[i].size())
                continue;

            bool match = true;
            for (int k = 0; k < user_id[j].size(); k++)
            {
                if (banned_id[i][k] == '*' || banned_id[i][k] == user_id[j][k])
                    continue;
                else
                {
                    match = false;
                    break;
                }
            }

            if (match)
                mask |= (1 << j);
        }
        
        candidates.push_back(mask);
    }

    dfs(0, 0, user_id, candidates, used, answer);

    return answer;
}