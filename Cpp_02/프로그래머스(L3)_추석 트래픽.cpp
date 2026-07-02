// 프로그래머스(L3) : 추석 트래픽
// 문제
// 1. 초당 최대 처리량 구하기
// 조건
// 1. 입력 3파트
//  1-1. 2016-09-15 (고정)
//  1-2. hh:mm::ss.sss (응답완료 시간)
//  1-3. t (처리시간), 0.001 <= t <= 3.000 (타임아웃이 3초)
// 풀이
// 1. 시간 변환 
//  1-1. 밀리초 단위 변환
// 2. 구간확인
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int timeToMs(const string& time) {
    static const int MS_SEC = 1000;
    static const int MS_MIN = 60000;
    static const int MS_HOUR = 3600000;

    int hour = stoi(time.substr(0, 2)) * MS_HOUR;
    int minu = stoi(time.substr(3, 2)) * MS_MIN;
    int sec = (int)(stod(time.substr(6, 6)) * MS_SEC);
    return hour + minu + sec;
}

int solution(vector<string> lines) {
    int answer = 0;

    static const string DATE = "2016-09-15";
    static const string TIME = "00:00:00.000";
    int timeIndex = DATE.size() + 1;
    int durationIndex = timeIndex + TIME.size() + 1;

    vector<pair<int, int>> segments(lines.size());
    for (int i = 0; i < lines.size(); i++) {
        string t = lines[i].substr(timeIndex, TIME.size());
        string d = lines[i].substr(durationIndex);
        d.pop_back();

        int msT = timeToMs(t);
        int msD = (int)(stod(d) * 1000);
        segments[i] = { msT - msD + 1, msT };
    }

    for (int i = 0; i < segments.size(); i++) {
        int s = segments[i].second;
        int e = s + 999;

        int count = 0;
        for (int j = 0; j < segments.size(); j++) {
            int ls = segments[j].first;
            int le = segments[j].second;
            if (!(ls > e || le < s)) count++;
        }

        answer = max(answer, count);
    }

    return answer;
}