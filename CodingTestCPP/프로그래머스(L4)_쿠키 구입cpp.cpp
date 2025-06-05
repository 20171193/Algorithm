// ���α׷��ӽ�(L4) : ��Ű ����
// ��������
// N^2 ����
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> cookie) {
    int answer = 0;

    for (int mid = 0; mid < cookie.size() - 1; mid++)
    {
        int left = mid;
        int right = mid + 1;
        int lSum = cookie[left];
        int rSum = cookie[right];

        while (left >= 0 && right < cookie.size())
        {
            if (lSum == rSum)
                answer = max(answer, lSum);

            if (lSum <= rSum && left > 0)
                lSum += cookie[--left];
            else if (rSum < lSum && right < cookie.size() - 1)
                rSum += cookie[++right];
            else
                break;
        }

    }

    return answer;
}