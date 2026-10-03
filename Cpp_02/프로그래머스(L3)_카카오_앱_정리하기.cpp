// 프로그래머스(L3) : 카카오 앱 정리하기
// 문제
// 1. 앱을 이동시키면 해당 방향으로 인접한 앱들이 모두 이동
// 2. 앱이 격자 밖으로 이동하면 반대 방향으로 나옴
//  2-1. 2*2이상의 앱의 한쪽만 격자 밖으로 이동하더라도 2*2크기로 반대 방향으로 나옴
// 조건
// 1. 보드 n*m : 2<=n<=10
// 2. 앱 board[i][j] : 0<=board[i][j]<=100
// 3. 이동 커맨드 commands : 1<=commands.size()<=1000
//  3-1. 방향 1-based : 우,하,좌,상
// 풀이
// 1. 매핑
//  1-1. 앱 좌표 매핑
//  1-2. 앱 크기 매핑(행,열)
// 2. 이동 스택 or 재귀(dfs)
//  2-1. command부터 arrow 방향에 인접한 앱들 스택 할당
//  2-2. command턴마다 중복 방지용 배열(크기 100)
// TODO : 무한 이동 처리(2번 예제)
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

int MAX_ROW, MAX_COL;
// 앱 정보
vector<vector<pair<int, int>>> appPoses;
vector<pair<int, int>> appSizes;

// 우,하,좌,상 (1-based)
int dc[5] = { 0,1,0, -1,0 };
int dr[5] = { 0,0,-1,0,1 };

// 재귀
void move(int curID, vector<bool>& moved, vector<vector<int>>& board, const vector<int>& command) {
    moved[curID] = true;
    int arrow = command[1];

    bool overLine = false;
    vector<pair<int, int>> tempPos;
    for (auto& pos : appPoses[curID]) {
        int nr = pos.first + dr[arrow];
        int nc = pos.second + dc[arrow];
        // 격자를 넘어간 경우
        if (nr < 0 || nr >= MAX_ROW || nc < 0 || nc >= MAX_COL) {
            overLine = true;
            break;
        }

        // 인접한 다른 앱이 존재하는 경우
        int nextID = board[nr][nc];
        if (nextID && nextID != curID && !moved[nextID])
            move(board[nr][nc], moved, board, command);

        tempPos.push_back({ nr, nc });
    }

    // 격자를 넘어간 경우
    if (overLine) {
        // 다음 위치 재할당
        tempPos.clear();

        // 열방향 이동 / 행방향 이동
        int moveVal = arrow % 2 == 0 ? appSizes[curID].second : appSizes[curID].first;
        for (auto& pos : appPoses[curID]) {
            int nr = (MAX_ROW + (pos.first + dr[arrow] * moveVal)) % MAX_ROW;
            int nc = (MAX_COL + (pos.second + dc[arrow] * moveVal)) % MAX_COL;

            // 인접한 다른 앱이 존재하는 경우
            int nextID = board[nr][nc];
            if (nextID && nextID != curID && !moved[nextID])
                move(board[nr][nc], moved, board, command);

            tempPos.push_back({ nr, nc });
        }
    }

    cout << "Move : " << curID << " Size : " << tempPos.size() << '\n';

    // 보드 반영, 맵 갱신
    for (auto& pos : appPoses[curID]) {
        if (board[pos.first][pos.second] == curID)
            board[pos.first][pos.second] = 0;
    }
    for (int i = 0; i < tempPos.size(); i++) {
        board[tempPos[i].first][tempPos[i].second] = curID;
        appPoses[curID][i] = tempPos[i];
    }
}

void print(const vector<vector<int>>& board) {
    for (const auto& rows : board) {
        for (const auto& num : rows) {
            cout << num;
        }
        cout << '\n';
    }
}

vector<vector<int>> solution(vector<vector<int>> board, vector<vector<int>> commands) {
    vector<vector<int>> answer;

    MAX_ROW = board.size();
    MAX_COL = board[0].size();

    appPoses.assign(101, {});
    appSizes.assign(101, { 0,0 });

    // 앱 매핑
    for (int r = 0; r < MAX_ROW; r++) {
        for (int c = 0; c < MAX_COL; c++) {
            int id = board[r][c];
            if (id) {
                // 이전에 삽입한 행과 다른 행에서 삽입된 경우
                if (!appPoses[id].empty() && appPoses[id].back().first != r) {
                    if (appSizes[id].second == 0)
                        appSizes[id].second = appPoses[id].size();  // 열 크기 할당
                    appSizes[id].first++;   // 행 크기 갱신
                }

                // 좌표 할당
                appPoses[id].push_back({ r,c });

                appSizes[id] = { max(1, appSizes[id].first), max(1, appSizes[id].second) };
            }
        }
    }

    cout << "INIT\n";
    print(board);
    cout << '\n';

    vector<bool> moved(101, false);
    for (const auto& command : commands) {
        move(command[0], moved, board, command);
        fill(moved.begin(), moved.end(), false);

        cout << "MOVE : (" << command[0] << ',' << command[1] << ") \n";
        print(board);
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);


    // 1. board
    vector<vector<int>> board = {
    {0, 9, 1, 1, 6, 0, 0, 0},
    {2, 2, 1, 1, 0, 0, 0, 0},
    {2, 2, 3, 4, 4, 4, 0, 0},
    {5, 0, 0, 4, 4, 4, 7, 0},
    {0, 0, 0, 4, 4, 4, 8, 8},
    {0, 0, 0, 0, 0, 0, 8, 8}
    };

    // 2. commands
    vector<vector<int>> commands = {
    {2, 1},
    {3, 1},
    {9, 2},
    {4, 1}
    };

    solution(board, commands);

    // 3. result (기대 결괏값 확인용)
    vector<vector<int>> expected_result = {
        {0, 0, 2, 2, 0, 0, 0, 0},
        {4, 4, 2, 2, 0, 0, 0, 0},
        {4, 4, 0, 3, 3, 3, 1, 0},
        {0, 0, 0, 3, 3, 3, 0, 0},
        {6, 0, 0, 3, 3, 3, 5, 5},
        {0, 0, 0, 0, 0, 0, 5, 5}
    };


    return 0;
}