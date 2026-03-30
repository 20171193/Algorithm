#include <string>
#include <vector>
#include <map>
#include <queue>
#include <iostream>
using namespace std;

// 1.많이 재생된 장르
// 2.장르 내에서 많이 재생된 노래
// 3.고유 번호가 낮은 노래

struct compare
{
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        if (a.second == b.second)
            return a.first < b.first;

        return a.second > b.second;
    }
    bool operator()(pair<string, int> a, pair<string, int> b)
    {
        if (a.second == b.second)
            return false;

        return a.second < b.second;
    }
};

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;

    map<string, priority_queue<pair<int, int>, vector<pair<int, int>>, compare>> infos;
    map<string, int> orders;

    for (int i = 0; i < plays.size(); i++)
    {
        if (infos.find(genres[i]) == infos.end())
        {
            priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
            pq.push({ i, plays[i] });
            infos.insert({ genres[i], pq });
            orders.insert({ genres[i], plays[i] });
        }
        else
        {
            infos[genres[i]].push({ i, plays[i] });
            orders[genres[i]] += plays[i];
        }
    }


    return answer;
}