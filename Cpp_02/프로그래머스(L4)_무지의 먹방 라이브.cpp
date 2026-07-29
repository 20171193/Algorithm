// 프로그래머스(L4) : 무지의 먹방 라이브
// https://school.programmers.co.kr/learn/courses/30/lessons/42891
// 문제
// 1. 회전판에 음식이 1번부터 N번까지 놓여있고, 1번부터 순서대로 1초씩 섭취.
//    마지막 음식(N번)까지 섭취하면 다시 1번 음식부터 섭취(반복).
// 2. 음식의 섭취시간이 다 되면 그 음식은 회전판에서 제거되고 다음 음식으로 넘어감.
// 3. K초 후 네트워크 장애가 발생했을 때, 다시 섭취를 시작해야 할 음식의 번호를 반환.
//    모든 음식을 K초 안에 다 먹었다면 -1 반환.
// 조건
// 1. food_times : 음식 N개의 섭취시간 배열
//    - 정확성 테스트 : 1 <= length <= 2,000 / 1 <= food_times[i] <= 1,000
//    - 효율성 테스트 : 1 <= length <= 200,000 / 1 <= food_times[i] <= 100,000,000
// 2. k : 네트워크 장애까지의 시간(초)
//    - 정확성 테스트 : 1 <= k <= 2,000,000
//    - 효율성 테스트 : 1 <= k <= 2 x 10^13  (long long 필요)
// 풀이
// 1. 음식 섭취 : k+1에 어떤 음식을 섭취해야 하는지
// 2. (섭취 시간,인덱스) min-heap 구성
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

int solution(vector<int> food_times, ll k) {
    int answer = -1;

	int cursor = 0;
	// pair<food_times, index>
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
	for(int i =0; i<food_times.size(); i++) 
		pq.push({food_times[i], i});
	
	int remain = food_times.size();
	ll prevFoodTime = 0;  // 직전에 pop한 음식의 시간값
	ll elapsed = 0;       // 경과시간

	while(!pq.empty()){
		auto cur = pq.top();
		pq.pop();

		// 현재 음식을 모두 먹어치우는 시간
		ll reps = (ll)remain * (cur.first - prevFoodTime);
		if(k < elapsed + reps){
			ll diff = k - elapsed;

			int targetIdx = diff % remain;
			for(int i = 0; i< food_times.size(); i++){
				if(food_times[i] > prevFoodTime) {
					if(targetIdx-- == 0)
						answer = i + 1;
				}
			}
			break;
		}

		elapsed += reps;
		prevFoodTime = cur.first;
		remain--;
	}

    return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	struct TestCase { vector<int> food_times; ll k; int expected; };

	vector<TestCase> testCases = {
		{ {3,1,2}, 5, 1 }, // 공식 예제 1
	};

	for (auto& tc : testCases) {
		int result = solution(tc.food_times, tc.k);
		cout << "k=" << tc.k
			 << " | expected: " << tc.expected
			 << " | result: " << result
			 << " | " << (result == tc.expected ? "PASS" : "FAIL") << "\n";
	}

	return 0;
}
