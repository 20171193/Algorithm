// 프로그래머스(L3) : 퍼즐 조각 채우기
// 조건
// 1. 조각은 회전 가능, 뒤집기 불가
// 2. 조각을 빈 공간에 채운 경우 인접한 다른 빈 공간이 존재하면 안됨.
//    ***즉, 조각과 빈공간 1:1매칭
// 3. 게임 보드에 조각을 최대한 많이 채워 넣고, 총 몇 칸을 채울 수 있는지 출력
// 풀이
// 1. 영역 BFS : table에 속한 조각
// 2. 영역에 놓을 수 있는 가장 큰 조각부터 놓기
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int BOARD_MAX = 51;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void normalize(vector<pair<int, int>>& area);

struct Piece {
    int size;
    vector<vector<pair<int, int>>> shapes;

    Piece(vector<pair<int, int>> shape) : size(shape.size()), shapes({ shape }) {
        // 조각 회전
        for (int i = 0; i < 3; i++)
            shapes.push_back(rotate90(shapes[i]));

        // 정규화 및 좌표 정렬
        for (auto& s : shapes) {
            normalize(s);
            sort(s.begin(), s.end());
        }
    }

    // 조각 회전(정규화 되지 않음, 음수 좌표)
    vector<pair<int, int>> rotate90(const vector<pair<int, int>>& prev) {
        vector<pair<int, int>> res(prev.size());
        // (r,c) -> (c,-r)
        for (int i = 0; i < (int)prev.size(); i++) {
            res[i].first = prev[i].second;
            res[i].second = -prev[i].first;
        }
        return res;
    }
};

vector<pair<int, int>> GetArea(int r, int c, vector<vector<int>>& board, vector<vector<char>>& visited) {
    if (board.size() < 1 || board[0].size() < 1
        || r < 0 || r >= (int)board.size()
        || c < 0 || c >= (int)board[0].size()
        || visited[r][c])
        return {}; // 예외

    int row = board.size(), col = board[0].size(), type = board[r][c];

    vector<pair<int, int>> area;
    queue<pair<int, int>> q;
    q.push({ r, c });
    visited[r][c] = 1;
    area.push_back({ r, c });

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int ny = cur.first + dy[d];
            int nx = cur.second + dx[d];
            if (ny < 0 || ny >= row || nx < 0 || nx >= col) continue;
            if (board[ny][nx] != type) continue;
            if (visited[ny][nx]) continue;

            q.push({ ny, nx });
            visited[ny][nx] = 1;
            area.push_back({ ny, nx });
        }
    }

    return area;
}

void normalize(vector<pair<int, int>>& area) {
    // 좌표 정규화
    int minR = BOARD_MAX, minC = BOARD_MAX;
    for (auto& p : area) {
        minR = min(minR, p.first);
        minC = min(minC, p.second);
    }

    for (auto& p : area) {
        p.first -= minR;
        p.second -= minC;
    }
}

bool place(Piece& piece, vector<pair<int, int>>& area) {
    for (auto& shape : piece.shapes) {
        if (shape == area)
            return true;
    }
    return false;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = 0;

    // 보드 행/열 == 테이블 행/열
    int row = game_board.size(), col = game_board[0].size();

    vector<vector<char>> visitedBoard(row, vector<char>(col, 0));
    auto visitedTable = visitedBoard;

    // 조각 할당 (테이블)
    vector<Piece> pieces;
    // 빈 영역 할당 (보드)
    vector<vector<pair<int, int>>> emptyAreas;

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (table[r][c] && !visitedTable[r][c]) {
                auto pieceShape = GetArea(r, c, table, visitedTable);
                // 생성자에서 좌표 정규화/정렬
                pieces.push_back(Piece(pieceShape));
            }

            if (!game_board[r][c] && !visitedBoard[r][c]) {
                emptyAreas.push_back(GetArea(r, c, game_board, visitedBoard));
                auto& ref = emptyAreas.back();
                // 좌표 정규화/정렬
                normalize(ref);
                sort(ref.begin(), ref.end());
            }
        }
    }

    // 공간-조각 매칭
    vector<char> used(pieces.size(), 0);
    for (auto& area : emptyAreas) {
        for (int i = 0; i < (int)pieces.size(); i++) {
            if (used[i]) continue;

            if (place(pieces[i], area)) {
                answer += area.size();
                used[i] = 1;
                break;
            }
        }
    }

    return answer;
}