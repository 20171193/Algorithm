// 프로그래머스(L4) : 블록 게임
// 문제
// 1. 1*1짜리 블록을 '위'에서 떨어뜨려 없앨 수 있는 블록의 최대 개수
//   : 속이 꽉찬 직사각형을 만들면 없어짐.
// 이전 풀이 (실패)
// 1. 같은 열, 윗 행에 블록이 존재하면 절대 삭제할 수 없는 구조로 보고
//    같은 '열'을 공유하는 블록 간 인접 그래프 + 진입차수(위상정렬)로 접근.
// 2. 실패 이유 : 블록 자신의 bounding box 밖에 있는 블록까지도
//    "같은 열의 가장 가까운 위 블록"이라는 이유로 의존관계로 잡아버림
//    (자신의 열이 이미 자기 셀로 꽉 차 있어 실제로는 아무 영향 없는 경우에도 간선이 생김)
// 수정
// 1. 위상정렬 폐기 -> 브루트포스(라운드 반복) 시뮬레이션으로 변경
// 2. 블록별로 열 단위 top/bottom을 구해 "채워야 하는 좌표(gap)"를 직접 계산
//    (GetMissingPos), 그 좌표 바로 위 칸부터 보드 최상단까지 다른 블록이
//    있는지 확인해서(CanDestroy) 제거 가능 여부 판단
// 3. 매 라운드마다 제거 가능한 블록들을 한꺼번에 지우고, 더 이상 지울 게
//    없을 때까지 반복 -> 연쇄 제거를 자연스럽게 반영
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 채워야하는 좌표 반환 {minRow(topRow), col}
vector<pair<int, int>> GetMissingPos(const vector<pair<int,int>>& block){
    int minRow = 51, maxRow = -1;
    for(auto& p : block){
        minRow = min(minRow, p.first);
        maxRow = max(maxRow, p.first);
    }

    // col -> {topRow, bottomRow}
    unordered_map<int, pair<int,int>> colRange;
    for(auto& p : block){
        int r = p.first, c = p.second;
        if(colRange.find(c) == colRange.end())
            colRange[c] = {r, r};
        else{
            colRange[c].first = min(colRange[c].first, r);
            colRange[c].second = max(colRange[c].second, r);
        }
    }

    vector<pair<int, int>> poses;
    for(auto& kv : colRange){
        int col = kv.first;
        int topRow = kv.second.first;
        int bottomRow = kv.second.second;

        // 위쪽만 존재하는 경우(아래쪽 구멍)
        if(bottomRow != maxRow) return {{-1,-1}};
        if(topRow != minRow) poses.push_back({topRow, col});
    }

    return poses;
}

// 지울 수 있는지 반환
// 채워야할 좌표 위(--)로 순회하며 다른 블록이 있다면 false, 없다면 true
bool CanDestroy(const vector<pair<int,int>>& missingPoses, const vector<vector<int>>& board){
    for(auto p : missingPoses){
        for(int row = p.first-1; row >= 0; row--){
            if(board[row][p.second])
                return false;
        }
    }
    return true;
}

int solution(vector<vector<int>> board) {
    int answer = 0;

    // 블록 영역 할당
    unordered_map<int, vector<pair<int,int>>> blocks;

    int n = board.size();
    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
            if(board[r][c]) blocks[board[r][c]].push_back({r,c});
        }
    }

    // 정렬 + 빈 좌표 할당
    unordered_map<int, vector<pair<int,int>>> missingPoses;
    for(auto& kv : blocks){

        auto poses = GetMissingPos(kv.second);
        if(!poses.empty() && poses.front().first == -1) continue;

        missingPoses[kv.first] = poses;
    }

    while(!blocks.empty()){
        vector<int> destroyed;

        for(auto& kv : missingPoses) {
            if(CanDestroy(kv.second, board)) {
                for(auto p : blocks[kv.first]) board[p.first][p.second] = 0;

                destroyed.push_back(kv.first);
            }
        }

        if(destroyed.empty()) break;

        for(auto key : destroyed) {
            answer++;
            blocks.erase(key);
            missingPoses.erase(key);
        }
    }

    return answer;
}
