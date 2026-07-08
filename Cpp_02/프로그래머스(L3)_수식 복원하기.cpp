// 프로그래머스(L3) : 수식 복원하기
// 문제
// 1. "2~9"진법으로 표현된 수식이 여러 개 주어짐.
//    결과가 X로 나오는 수식이 존재할 경우, 그 수식을 복원하여 반환.
//    (여러 값으로 표현될 수 있으면 "= ?" 반환)
// 조건
// 1. 수식 개수 : 1~100
// 2. 진법 : 2~9
// 3. 입력 : "00 +(-) 00 = 00"
// 풀이
// 1. 후보 필터링 : 입력 최댓값 i(진법은 최소 i+1)
// 2. 후보 검증 : 각 수식에 (i+1 ~ 9진법)대입 및 검증
// 3. 중복 확인
//  3-1. 방정식의 해가 하나 : 해당 수 반환
//  3-2.    ""    여러 개 : ? 반환
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

// 수식 변환
// {+(-),a,b,c}
vector<string> SplitExpression(const string& exp, int& mxBaseNum){
	vector<string> ret;

	string temp;
	for(int i =0; i<exp.size(); i++){
		if(exp[i] == ' ') {
            if(temp == "=") {
                temp = "";
                continue;
            }

			ret.push_back(temp);
			temp = "";
		}
		else {
			if('0' < exp[i] && exp[i] < '9')
				mxBaseNum = max(mxBaseNum, exp[i] - '0' + 1);
			temp += exp[i];
		}
	}
	ret.push_back(temp);

	swap(ret[0], ret[1]);
	return ret;
}

// n진수 문자열 -> 10진수 정수 변환
int BaseToDec(const string& numstr, int baseNum){
	int digit = 0, ret = 0;
	for(auto iter = numstr.rbegin(); iter!= numstr.rend(); iter++)
		ret += ((*iter) - '0') * (int)round(pow(baseNum, digit++));
	return ret;
}

// 10진수 정수  -> n진수 문자열 변환
string DecToBase(int num, int baseNum){
    if (num == 0) return "0";
    string ret = "";
    while (num > 0) {
        ret = to_string(num % baseNum) + ret;
        num /= baseNum;
    }
    return ret;
}

// baseNum진법 적용 수식 검증
bool Check(const vector<string>& exp, int baseNum){
	int a = BaseToDec(exp[1], baseNum);
	int b = BaseToDec(exp[2], baseNum) * (exp[0][0] == '+' ? 1 : -1);
	int c = BaseToDec(exp[3], baseNum);
    return a + b == c;
}

vector<string> solution(vector<string> expressions) {
	vector<string> answer;

	int n = expressions.size();

	int mxBaseNum = -1;

	// 수식 분리, 방정식 구분
	vector<vector<string>> exps;
	for(int i =0; i<n; i++){
		if(expressions[i].back() == 'X')
			answer.push_back(expressions[i]);
		exps.push_back(SplitExpression(expressions[i], mxBaseNum));
	}

	// 수식 검증
	vector<int> enableNum;
	for(int baseNum = mxBaseNum; baseNum <= 9; baseNum++){
		bool success = true;
		for(const vector<string>& exp : exps){
            if(exp.back() == "X") continue;
			if(!Check(exp, baseNum)){
				success = false;
				break;
			}
		}

		if(success) enableNum.push_back(baseNum);
	}

	// 중복 확인, 정답 처리
	for(string& str : answer){
		vector<string> exp = SplitExpression(str, mxBaseNum);

		int result = -1;
		for(int baseNum : enableNum){
            int a = BaseToDec(exp[1], baseNum);
            int b = (BaseToDec(exp[2], baseNum) * (exp[0][0] == '+' ? 1 : -1));
            int res = stoi(DecToBase(a + b, baseNum));

			if(result == -1) result = res;
			else if(res != result) {
				result = -1;
				break;
			}
		}

		str.pop_back();
		if(result == -1) str += '?';
		else str += to_string(result);
	}

    return answer;
}
