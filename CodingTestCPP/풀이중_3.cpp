// 백준 13128번 : 특수부대(CH)
// 조건
// 1. 수레
//  1-1. 속력 : p m/s (수레와 같은 위치에 있는 요원의 수 p)
//  1-2. 이동 : 도착 지점으로 이동
//              요원 탑승 시 무조건 수레와 함께 이동(요원 속력은 무시)
// 2. 요원
//  2-1. 요원은 초기 위치, 초기 체력, 이동 속력을 가짐.
//  2-2. 위치(0<=X<=1,000), 체력(150<=H<=600), 속력 m/s(1<=S<=1,000)
//  2-3. 항상 수레를 향해 움직임(수레에 탑승하지 못한 요원)
// 3. 총격
//  3-1. 총격으로 체력이 0이 된 요원은 사망한 시점으로부터
//       10초 뒤 자신의 초기위치에서 가득찬 체력으로 살아남
// 4. 그 외
//  4-1. 입력은 모두 정수
//  4-2. 사망한 요원이 총격을 받은 경우는 무시
//  4-3. 부활 시간 == 총격 시간인 경우 부활 후 총격을 받은 것으로 간주 
// 
// 입력
// 1. 1줄 : 수레 위치 s(0<=s<=1,000), 목표 지점 좌표e(0<=e<=1,000)
// 2. 2줄 : 요원의 수 m(1<=m<=10)
// 3. ~m줄 : 요원 초기 위치x(0<=x<=1,000), 초기 체력h(150<=h<=600), 이동 속력s(1<=s<=1,000) 
// 4. m+1줄 : 발생한 모든 총격의 수(1<=l<=100)
// 5. ~l줄 : 요원의 번호a(1<=a<=m), 시각b(0<=b<=1,000), 데미지d(1<=d<=600)
// 6. l+1줄 : 수레의 위치를 알고 싶은 시각의 수q(1<=q<=1,000)
// 7. ~q줄 : 시각(0<=t<=1,000)  
//
// 출력
// 1. 수레의 위치를 알고 싶은 시각마다 당시 수레의 좌표 출력
//  1-1. 절대/상대 오차가 10^-6 이하
// 
// 풀이
// 1. t시간에 발생하는 이벤트 순서
//  1-1. 요원 부활
//  1-2. 총격
//  1-3. 수레 이동
//  1-4. 요원 이동
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Agent {
	bool onCart = false;
	int pos, hp, speed, curPos, curHp;
	Agent() {}
	Agent(int pos, int hp, int speed) : pos(pos), curPos(pos), hp(hp), curHp(hp), speed(speed) {}

	void Regen(int cartPos) {
		curPos = pos;
		curHp = hp;
		onCart = curPos == cartPos;
	}
	void Move(int cartPos) {

		curPos = curPos + (cartPos < curPos ? -1 : 1) * speed;
		if (cartPos == curPos) onCart = true;
	}
};

int s, e, m, l, q, maxTime = 0, query[1001];
int cartSpeed, cartPos;

// 각 시간 별 수레 위치
double timeToPos[1001];

Agent agents[11];
queue<pair<int, int>> regenEvent;
unordered_map<int, vector<pair<int, int>>> timeToShoot;

// 부활 이벤트 기반 부활 처리
// 동시에 부활 위치기반 수레 탑승 처리
void RegenAgents(int curTime) {
	if (!regenEvent.empty()) {
		while (curTime == regenEvent.front().first) {
			agents[regenEvent.front().second].Regen(cartPos);
			regenEvent.pop();
		}
	}
}

// 총격/사망 처리 및 부활 이벤트 등록
void ShootAgents(int curTime) {
	auto shootIter = timeToShoot.find(curTime);
	if (shootIter == timeToShoot.end()) return;

	for (auto& info : (*shootIter).second) {
		int num = info.first, damage = info.second;
		if (agents[num].curHp <= 0) continue;

		agents[num].curHp -= damage;
		// 사망처리 (부활 이벤트 등록)
		if (agents[num].curHp <= 0)
			regenEvent.push({ curTime + 10, num });
	}
}

// 요원 이동 및 수레 탑승(수레/사망한 요원 제외)
// 다음 카트 속력 결정
void MoveAgents() {
	int onCartCount = 0;
	for (int i = 1; i <= m; i++) {
		if (!agents[i].onCart && agents[i].curHp > 0)
			agents[i].Move();

		if (agents[i].onCart) onCartCount++;
	}
	cartSpeed = onCartCount;
}

// 수레 이동 처리
void MoveCart() {

}

void solution() {
	for (int curTime = 0; curTime <= maxTime; curTime++) {
		// 1. 요원 부활
		RegenAgents(curTime);
		// 2. 총격
		ShootAgents(curTime);
		// 3. 수레 이동
		MoveCart();
		// 4. 요원 이동
		MoveAgents();
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> s >> e;
	cin >> m;

	// 요원정보 1-based
	for (int i = 1; i <= m; i++) {
		int pos, hp, speed;
		cin >> pos >> hp >> speed;
		agents[i] = Agent(pos, hp, speed);
	}

	cin >> l;
	// 총격정보 0-based
	for (int i = 0; i < l; i++) {
		int num, time, damage;
		cin >> num >> time >> damage;
		timeToShoot[num].push_back({ time, damage });
	}

	cin >> q;
	// 쿼리 0-based
	for (int i = 0; i < q; i++) {
		cin >> query[i];
		maxTime = max(maxTime, query[i]);
	}

	solution();

	for (int i = 0; i < q; i++)
		cout << timeToPos[query[i]] << '\n';

	return 0;
}