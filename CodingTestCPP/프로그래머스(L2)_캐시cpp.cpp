#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <algorithm>
using namespace std;

// LRU �˰��� 
// : ���� �������� �������� ���� �������� ��ü�ϴ� ���

// FIFO : ����� �ð��� �������� ��ü�� �������� �����ϴ� ���
// LFU : ���� ���� Ƚ���� �����ϴ� �������� ��ü
// LRU : ���� �������� �������� ���� �������� ��ü

// cache hit : ��û�� �����Ͱ� ĳ�ÿ� �����ϴ� ���
// cache miss : ��û�� �����Ͱ� ĳ�ÿ� ���������ʴ� ���


string Toupper(const string& str)
{
    stringstream ss;
    for (char c : str)
        ss << toupper(c);
    return ss.str();
}

bool FindIndex(const vector<pair<int, string>>& cache, const string& str, int& retIndex)
{
    // ĳ�� ��Ʈ : return true, retIndex = hitIndex
    // ĳ�� �̽� : return false, retIndex = lruIndex
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

        // ĳ�� ��Ʈ
        if (FindIndex(cache, cur, findIndex))
        {
            answer += 1;
            cache[findIndex].first = i;
        }
        // ĳ�� �̽�
        else
        {
            answer += 5;
            cache[findIndex] = { i, cur };
        }
    }

    return answer;
}