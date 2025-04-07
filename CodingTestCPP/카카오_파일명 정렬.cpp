#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Form
{
    string head;
    int num;
    int index;
};

bool cmp(const Form& a, const Form& b)
{
    if (a.head == b.head && a.num == b.num)
        return a.index < b.index;
    else if (a.head == b.head)
        return a.num < b.num;
    else
        return a.head < b.head;
}

vector<string> solution(vector<string> files) {
    vector<string> answer(files.size());

    vector<Form> forms(files.size());
    for (int i = 0; i < files.size(); i++)
    {
        string head, num;
        for (int j = 0; j < files[i].size(); j++)
        {
            char c = files[i][j];

            if (c >= '0' && c <= '9')
                num += c;
            else
            {
                if (num.size() > 0)
                    break;

                head += toupper(c);
            }
        }
        forms[i] = { head, stoi(num), i };
    }

    sort(forms.begin(), forms.end(), cmp);

    for (int i = 0; i < forms.size(); i++)
        answer[i] = files[forms[i].index];

    return answer;
}