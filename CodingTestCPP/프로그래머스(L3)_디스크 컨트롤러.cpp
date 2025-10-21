#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

// 1. 소요시간
// 2. 요청시각
// 3. 번호

struct Process {
    int num, reqTime, pcsTime;
    bool operator<(const Process& other) const {
        return reqTime < other.reqTime;
    }
};

struct Comparer
{
    bool operator()(const Process& a, const Process& b) const {
        if (a.pcsTime != b.pcsTime)
            return a.pcsTime > b.pcsTime;
        if (a.reqTime != b.reqTime)
            return a.reqTime > b.reqTime;
        return a.num > b.num;
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;

    int n = jobs.size();
    vector<Process> pcss(n);
    for (int i = 0; i < n; i++)
        pcss[i] = { i, jobs[i][0], jobs[i][1] };

    sort(pcss.begin(), pcss.end());

    priority_queue<Process, vector<Process>, Comparer> pq;

    int curTime = 0;
    for (int i = 0; i < pcss.size(); i++)
    {
        curTime = max(curTime, pcss[i].reqTime);
        pq.push(pcss[i]);

        while (!pq.empty() && (i < pcss.size() - 1 && curTime < pcss[i + 1].reqTime))
        {
            Process cur = pq.top();
            pq.pop();

            curTime += cur.pcsTime;
            answer += curTime - cur.reqTime;
        }
    }

    while (!pq.empty())
    {
        Process cur = pq.top();
        pq.pop();

        curTime += cur.pcsTime;
        answer += curTime - cur.reqTime;
    }

    return answer / pcss.size();
}

int main()
{
    solution({ {0, 3},{1, 9} , {3, 5} });

    return 0;
}