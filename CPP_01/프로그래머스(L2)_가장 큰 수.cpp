#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

string solution(vector<int> numbers) {
    string answer = "";

    vector<string> strNumbers(numbers.size());
    for (int i = 0; i < numbers.size(); i++)
        strNumbers[i] = to_string(numbers[i]);

    sort(strNumbers.begin(), strNumbers.end(),
        [](const string& a, const string& b)
        {
            return a + b > b + a;
        });

    stringstream ss;
    for (const string& str : strNumbers)
        ss << str;

    answer = ss.str();

    return answer;
}