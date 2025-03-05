#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool comp(const string& a, const string& b)
{
    if (stoi(a.substr(0, 2)) == stoi(b.substr(0, 2)))
        return stoi(a.substr(3, 2)) < stoi(b.substr(3, 2));

    return stoi(a.substr(0, 2)) < stoi(b.substr(0, 2));
}

int Convert(const string& time)
{
    return 60 * stoi(time.substr(0, 2)) + stoi(time.substr(3, 2));
}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";

    sort(timetable.begin(), timetable.end(), comp);

    int reps = 0, remainSit = 0, crueIdx = 0;
    int curTime = Convert("09:00");
    int maxTime = -1;

    while (n > reps)
    {
        curTime += reps * t;
        remainSit = m;

        for (crueIdx; crueIdx < timetable.size(); crueIdx++)
        {
            // 자리가 없는 경우
            if (remainSit < 1)
                break;
            // 늦게 온 경우
            if (Convert(timetable[crueIdx]) > curTime)
                break;

            remainSit--;
        }

        if (remainSit > 0)
            maxTime = curTime;

        reps++;
    }

    if (maxTime == -1)
        maxTime = Convert(timetable.front()) - 1;

    string hour = to_string(maxTime / 60);
    if (hour.size() < 2)
        hour = "0" + hour;

    string min = to_string(maxTime % 60);
    if (min.size() < 2)
        min = "0" + min;

    answer = hour + ":" + min;

    return answer;
}

int main()
{
    solution(2, 10, 2, { "09:00", "09:00", "09:00", "09:00" });

    return 0;
}