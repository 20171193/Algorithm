// 프로그래머스(L3) : 표 병합
// 조건
// 1. 함수
//  1-1. UPDATE r c value : (r,c)를 value로 변경
//  1-2. UPDATE value1 value2 : value1값을 가진 모든 셀을 value2로 변경
//  1-3. MERGE r1 c1 r2 c2 : 두 셀을 (r1, c1) 값으로 병합. 이후 선택 시 병합된 셀로 접근
//  1-4. UNMERGE r c : r, c 셀의 모든 병합 해제, (r,c)만 이전 값을 가짐
//  1-5. PRINT r c : r, c의 값을 출력 비어있을 경우 "EMPTY" 출력
// 풀이
// 1. 병합 노드 관리 : find재귀로 부모찾기
#include <string>
#include <vector>
#include <iostream>
using namespace std;

const int MAX_POS = 50;

pair<int,int> find(int r, int c, vector<vector<vector<pair<int, int>>>>& address) {
    if (address[r][c][0] == make_pair(r, c)) return { r,c };
    else return find(address[r][c][0].first, address[r][c][0].second, address);
}

void update(int r, int c, string value, vector<vector<string>>& table, vector<vector<vector<pair<int, int>>>>& address) {
    pair<int, int> base = find(r, c, address);
    table[base.first][base.second] = value;
}
void update(string value1, string value2, vector<vector<string>>& table, vector<vector<vector<pair<int, int>>>>& address) {
    for (int r = 1; r < table.size(); r++) {
        for (int c = 1; c < table[r].size(); c++) {
            if (table[r][c] == value1)
                table[r][c] = value2;
        }
    }
}
string print(int r, int c, vector<vector<string>>& table, vector<vector<vector<pair<int, int>>>>& address) {
    pair<int, int> base = find(r, c, address);
    string ret = table[base.first][base.second];

    if (ret.size() == 0) return "EMPTY";
    else return ret;
}
void merge(int r1, int c1, int r2, int c2, vector<vector<string>>& table, vector<vector<vector<pair<int, int>>>>& address) {
    pair<int, int> base = find(r1, c1, address);
    pair<int, int> target = find(r2, c2, address);
    if (base == target) return;

    string mergeValue = table[base.first][base.second].size() == 0
        ? table[target.first][target.second]
        : table[base.first][base.second];

    table[target.first][target.second] = "";
    table[base.first][base.second] = mergeValue;

    auto& baseVec = address[base.first][base.second];
    auto& moveVec = address[target.first][target.second];
    baseVec.insert(baseVec.end(), moveVec.begin(), moveVec.end());

    moveVec = { base };
}
void unmerge(int r, int c, vector<vector<string>>& table, vector<vector<vector<pair<int, int>>>>& address) {
    pair<int, int> base = find(r, c, address);
    string baseValue = table[base.first][base.second];

    // 자기 자신을 포함한 연결된 모든 셀 값, 주소 초기화
    for (auto iter = address[base.first][base.second].begin(); iter != address[base.first][base.second].end(); iter++) {
        int tr = (*iter).first, tc = (*iter).second;
        table[tr][tc] = "";
        address[tr][tc][0] = { tr,tc };
    }

    address[base.first][base.second] = {{ base.first, base.second }};

    // {r,c}만 이전 값으로 복구
    table[r][c] = baseValue;
}

void query(const string& command, vector<vector<string>>& table, vector<vector<vector<pair<int, int>>>>& address, vector<string>& prints) {
    vector<string> splits;
    int prev = 0;

    for (int i = 0; i < command.size(); i++) {
        if (command[i] == ' ') {
            splits.push_back(command.substr(prev, i - prev));
            prev = i + 1;
        }
    }
    splits.push_back(command.substr(prev, command.size() - prev));

    string& oper = splits[0];
    if (oper == "UPDATE") {
        if (splits.size() == 4)
            update(stoi(splits[1]), stoi(splits[2]), splits[3], table, address);
        else
            update(splits[1], splits[2], table, address);
    }
    else if (oper == "MERGE") {
        merge(stoi(splits[1]), stoi(splits[2]), stoi(splits[3]), stoi(splits[4]), table, address);
    }
    else if (oper == "UNMERGE") {
        unmerge(stoi(splits[1]), stoi(splits[2]), table, address);
    }
    else if (oper == "PRINT") {
        prints.push_back(print(stoi(splits[1]), stoi(splits[2]), table, address));
    }
}


vector<string> solution(vector<string> commands) {
    vector<string> answer;

    vector<vector<vector<pair<int, int>>>> address(MAX_POS + 1, vector<vector<pair<int, int>>>(MAX_POS + 1));
    vector<vector<string>> table(MAX_POS + 1, vector<string>(MAX_POS+1, ""));

    for (int r = 1; r <= MAX_POS; r++)
        for (int c = 1; c <= MAX_POS; c++)
            address[r][c].push_back({ r,c });

    for (const string& command : commands)
        query(command, table, address, answer);

    return answer;
}
