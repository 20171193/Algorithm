#include <string>
#include <vector>
#include <algorithm>
typedef long long ll;
using namespace std;

ll solution(vector<int> sequence) {
    ll answer = 0;

    int flag = 1;
    ll prevM = sequence[0] * -flag;
    ll prevP = sequence[0] * flag;
    flag *= -1;

    answer = max(prevM, prevP);

    for (int i = 1; i < sequence.size(); i++)
    {
        ll curM = max(prevM + sequence[i] * -flag, static_cast<ll>(sequence[i] * -flag));
        ll curP = max(prevP - sequence[i] * flag, static_cast<ll>(-sequence[i] * flag));

        answer = max({ curM, curP, answer });

        prevM = curM;
        prevP = curP;
        flag *= -1;
    }

    return answer;
}