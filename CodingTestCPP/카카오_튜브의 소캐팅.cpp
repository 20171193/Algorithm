// 2017 카카오 코드 본선 : 튜브의 소개팅
#include <vector>
#include <climits>
#include <queue>
using namespace std;
typedef long long ll;

struct Node {
    int _y, _x, _dist, _cost;
    Node(int y, int x, int dist, int cost) : _y(y), _x(x), _dist(dist), _cost(cost) {}
    bool operator>(const Node& other) const
    {
        if (_dist == other._dist)
            return _cost > other._cost;
        return _dist > other._dist;
    }
};

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, int s, vector<vector<int>> time_map) {
    int move_distance = INT_MAX;
    int sum_of_talk_time = INT_MAX;

    // 다익스트라
    int dx[4] = { 1,0,-1,0 };
    int dy[4] = { 0,-1,0,1 };
    vector<vector<int>> talkTimes(m, vector<int>(n, INT_MAX));
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({ 0,0,0,0 });
    talkTimes[0][0] = 0;

    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();

        int cx = cur._x, cy = cur._y, cd = cur._dist, cc = cur._cost;

        if (talkTimes[cy][cx] < cc)
            continue;

        if ((cx == n - 1 && cy == m - 1) && move_distance > cd)
        {
            move_distance = cd;
            sum_of_talk_time = cc;
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = cy + dy[i];
            int nx = cx + dx[i];
            if (ny < 0 || ny >= m || nx < 0 || nx >= n) continue;
            if (time_map[ny][nx] == -1) continue;
            if ((ll)cc + time_map[ny][nx] > s) continue;
            int nc = cc + time_map[ny][nx];
            if (talkTimes[ny][nx] <= nc) continue;

            pq.push({ ny,nx, cd + 1, nc });
            talkTimes[ny][nx] = nc;
        }
    }

    vector<int> answer(2);
    answer[0] = move_distance;
    answer[1] = sum_of_talk_time;

    return answer;
}