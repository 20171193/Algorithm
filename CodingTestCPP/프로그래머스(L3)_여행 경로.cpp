#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

bool cmp(pair<string, int>& a, pair<string, int>& b)
{
    return a.first < b.first;
}

bool dfs(string cur, vector<bool>& visited, vector<string>& path, map<string, vector<pair<string, int>>>& edges)
{
    if (path.size() == visited.size() + 1)
        return true;

    for (int i = 0; i < edges[cur].size(); i++)
    {
        if (visited[edges[cur][i].second])
            continue;

        string next = edges[cur][i].first;
        int nIdx = edges[cur][i].second;

        visited[nIdx] = true;
        path.push_back(next);

        if (dfs(next, visited, path, edges))
            return true;

        visited[nIdx] = false;
        path.pop_back();
    }
    return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;

    // pair<string, int>
    // first(string) : destination
    // second(int) : tickets index
    map<string, vector<pair<string, int>>> edges;
    for (int i = 0; i < tickets.size(); i++)
    {
        edges[tickets[i][0]].push_back({ tickets[i][1], i });
    }

    // 알파벳 순 정렬
    for (auto iter = edges.begin(); iter != edges.end(); iter++)
    {
        sort((*iter).second.begin(), (*iter).second.end(), cmp);
    }

    // 방문배열 할당
    vector<bool> visited(tickets.size(), false);

    // 시작지점 할당
    answer.push_back("ICN");
    dfs("ICN", visited, answer, edges);

    return answer;
}