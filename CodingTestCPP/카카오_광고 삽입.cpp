#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const int HOUR = 3600;
const int MIN = 60;

int GetSec(string time)
{
    // hh:mm:ss
    int hour = stoi(time.substr(0, 2));
    int min = stoi(time.substr(3, 2));
    int sec = stoi(time.substr(6, 2));

    return hour * HOUR + min * MIN + sec;
}

string GetStr(int time)
{
    string ret = "";

    string hour = to_string(time / HOUR);
    hour = hour.size() < 2 ? "0" + hour : hour;
    time %= HOUR;

    string min = to_string(time / MIN);
    min = min.size() < 2 ? "0" + min : min;
    time %= MIN;

    string sec = to_string(time);
    sec = sec.size() < 2 ? "0" + sec : sec;

    return hour + ":" + min + ":" + sec;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    int play = GetSec(play_time);
    int maxTime = play + 1;
    int adv = GetSec(adv_time);

    if (play == adv)
        return "00:00:00";

    vector<long long> pSum(maxTime, 0);

    for (const string& log : logs)
    {
        int s = GetSec(log.substr(0, 8));
        pSum[s] += 1;
        int e = GetSec(log.substr(9, 8));
        pSum[e] -= 1;
    }

    // 누적합으로 누적된 재생시간 할당
    for (int reps = 0; reps < 2; reps++)
        for (int i = 1; i < maxTime; i++)
            pSum[i] += pSum[i - 1];

    // 0초에 시작하는 광고를 고려 
    ll maxViewTime = pSum[adv - 1];
    int answer = 0;

    for (int i = adv; i <= maxTime; i++)
    {
        ll curViewTime = pSum[i] - pSum[i - adv];
        if (curViewTime > maxViewTime)
        {
            maxViewTime = curViewTime;
            answer = i - adv + 1;
        }
    }

    return GetStr(answer);
}