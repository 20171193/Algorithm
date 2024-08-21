// ���α׷��ӽ�
#include <string>
#include <vector>

using namespace std;

// ����� ����� �� = 0�� �� �� ����.
// -�� +�� ����?
// ������ ���� 2~20 -> ��Ʈ����ŷ ��밡��

int solution(vector<int> numbers, int target) {
    int answer = 0;

    for (int i = 0; i < (i << numbers.size()); i++)
    {
        int temp = 0;
        for (int j = 0; j < numbers.size(); j++)
        {
            if (i & (1 << j))
                temp -= numbers[j];
            else
                temp += numbers[j];
        }

        if (temp == target)
            answer++;
    }

    return answer;
}

int main()
{
    vector<int> numbers = { 1, 1, 1, 1, 1 };
    solution(numbers, 3);
    return 0;
}