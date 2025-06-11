#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <numeric>
#include <iostream>
using namespace std;

#define rank aaaa
// 영역 마킹 후 MST 구성

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

// rank by union
vector<int> root, rank;

// 마킹(방문처리)
vector<vector<int>> area;
int landSize, mark = 1;

// 좌표 해시
struct PosHash
{
    size_t operator()(const pair<int, int>& p) const
    {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};
// 영역 사이 간선
unordered_map<pair<int, int>, int, PosHash> edges;

bool comp(const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b)
{
    return a.second < b.second;
}

int Find(int a)
{
    // 경로 압축
    if (a != root[a])
        root[a] = Find(root[a]);

    return root[a];
}

void Union(int a, int b)
{
    int ra = Find(a);
    int rb = Find(b);

    if (rank[ra] > rank[rb])
        root[rb] = ra;
    else if (rank[ra] < rank[rb])
        root[ra] = rb;
    else
    {
        root[rb] = ra;
        rank[ra]++;
    }
}

void Marking(pair<int, int> start, const vector<vector<int>>& land, int height)
{
    queue<pair<int, int>> q;
    area[start.first][start.second] = mark;
    q.push(start);

    while (!q.empty())
    {
        int cy = q.front().first;
        int cx = q.front().second;
        int curHeight = land[cy][cx];
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = cy + dy[i];
            int nx = cx + dx[i];

            if (ny < 0 || ny >= landSize || nx < 0 || nx >= landSize)
                continue;
            // 현재 영역에 포함
            if (area[ny][nx] == mark)
                continue;

            int nextHeight = land[ny][nx];
            int diff = abs(nextHeight - curHeight);

            // 이동 불가능
            if (diff > height)
                continue;


            // 이동 가능할 경우 이어서 탐색
            area[ny][nx] = mark;
            q.push({ ny,nx });
        }
    }
}

void FindEdge(const vector<vector<int>>& land)
{
    for (int y = 0; y < landSize; y++)
    {
        for (int x = 0; x < landSize; x++)
        {
            int cMark = area[y][x], cHeight = land[y][x];

            // 오른쪽, 위(좌표 상) 영역만 확인
            for (int i = 0; i < 2; i++)
            {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (ny >= landSize || nx >= landSize) continue;
                int nMark = area[ny][nx];
                if (cMark == nMark) continue;

                int diff = abs(land[ny][nx] - cHeight);
                pair<int, int> edge = { min(cMark, nMark), max(cMark, nMark) };

                if (edges.find(edge) == edges.end())
                    edges.insert({ edge, diff });
                else
                    edges[edge] = min(edges[edge], diff);
            }
        }
    }
}

int solution(vector<vector<int>> land, int height) {
    int answer = 0;

    // 1. 영역 구분 (BFS)
    landSize = (int)land.size();
    area.assign(landSize, vector<int>(landSize, 0));

    for (int y = 0; y < landSize; y++)
    {
        for (int x = 0; x < landSize; x++)
        {
            if (area[y][x] != 0) continue;

            Marking({ y,x }, land, height);
            mark++;
        }
    }

    // 2. 영역 사이 간선도출
    FindEdge(land);

    // 3. 간선 연결 (MST)
    // mark == areaCount (1-based) 
    rank.assign(mark, 1);
    root.assign(mark, 0);
    // 최초 루트는 자기 자신 
    iota(root.begin(), root.end(), 0);

    vector<pair<pair<int, int>, int>> sortedEdges(edges.begin(), edges.end());
    sort(sortedEdges.begin(), sortedEdges.end(), comp);
    for (const pair<pair<int, int>, int>& edge : sortedEdges)
    {
        int s = edge.first.first;
        int e = edge.first.second;
        int cost = edge.second;

        if (Find(s) == Find(e)) continue;

        Union(s, e);
        answer += cost;
    }

    return answer;
}
