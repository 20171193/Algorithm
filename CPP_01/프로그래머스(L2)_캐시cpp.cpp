#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <algorithm>
using namespace std;

// LRU 알고리즘 
// : 가장 오랫동안 참조되지 않은 페이지를 교체하는 기법

// FIFO : 적재된 시간을 기준으로 교체될 페이지를 선정하는 기법
// LFU : 가장 적은 횟수를 참조하는 페이지를 교체
// LRU : 가장 오랫동안 참조되지 않은 페이지를 교체

// cache hit : 요청한 데이터가 캐시에 존재하는 경우
// cache miss : 요청한 데이터가 캐시에 존재하지않는 경우


string Toupper(const string& str)
{
    stringstream ss;
    for (char c : str)
        ss << toupper(c);
    return ss.str();
}

bool FindIndex(const vector<pair<int, string>>& cache, const string& str, int& retIndex)
{
    // 캐시 히트 : return true, retIndex = hitIndex
    // 캐시 미스 : return false, retIndex = lruIndex
    int lruIndex = -1, lruValue = 31;
    for (int i = 0; i < cache.size(); i++)
    {
        if (cache[i].second == "")
        {
            retIndex = i;
            return false;
        }

        if (cache[i].second == str)
        {
            retIndex = i;
            return true;
        }

        if (lruValue > cache[i].first)
        {
            lruValue = cache[i].first;
            lruIndex = i;
        }
    }

    retIndex = lruIndex;
    return false;
}

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;

    if (cacheSize == 0)
        return 5 * cities.size();

    vector<pair<int, string>> cache(cacheSize);
    for (int i = 0; i < cities.size(); i++)
    {
        string cur = Toupper(cities[i]);
        int findIndex = -1;

        // 캐시 히트
        if (FindIndex(cache, cur, findIndex))
        {
            answer += 1;
            cache[findIndex].first = i;
        }
        // 캐시 미스
        else
        {
            answer += 5;
            cache[findIndex] = { i, cur };
        }
    }

    return answer;
}