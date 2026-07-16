// 프로그래머스(L3) : 홀짝트리
// 문제
// 1. 루트가 정해지지 않은 포레스트(여러 트리)가 주어짐.
//    각 노드는 "번호의 홀/짝"과 "자식 개수의 홀/짝" 조합으로 4가지 유형 중 하나임.
//    - 홀수 노드   : 번호 홀수 & 자식 개수 홀수
//    - 짝수 노드   : 번호 짝수 & 자식 개수 짝수
//    - 역홀수 노드 : 번호 홀수 & 자식 개수 짝수
//    - 역짝수 노드 : 번호 짝수 & 자식 개수 홀수
// 2. 각 트리마다 루트를 어떻게 잡느냐에 따라
//    - 홀짝 트리   : 모든 노드가 홀수/짝수 노드로만 구성되는 경우
//    - 역홀짝 트리 : 모든 노드가 역홀수/역짝수 노드로만 구성되는 경우
//    가 될 수 있는 루트 후보 개수를 각각 구해서 반환.
// 조건
// 1. 노드 개수 : 1 ≤ nodes 길이 ≤ 400,000
// 2. 간선 개수 : 1 ≤ edges 길이 ≤ 1,000,000
// 3. 입력은 포레스트(트리들의 집합) 형태로만 주어짐
// 4. 0은 짝수로 취급
// 풀이
// 1. 각 노드를 루트로 트리 구성
// 2. 해당 트리 유형 파악
// 3. 최적화
//  3-1. 미리 간선 방향 별로 하위 트리 유형 파악
//  3-2. 루트 후보 별로 재귀
#include <string>
#include <vector>
#include <queue>
using namespace std;

enum TYPE
{
	NONE = -1,
	EVEN = 0,
	ODD,
	R_EVEN,
	R_ODD
};

TYPE GetType(int num, int cnt)
{
	bool numEven = num % 2 == 0;
	bool cntEven = cnt == 0 ? true : cnt % 2 == 0;
	if (numEven)
	{
		if (cntEven)
			return EVEN;
		else
			return R_EVEN;
	}
	else
	{
		if (cntEven)
			return R_ODD;
		else
			return ODD;
	}
}

vector<int> solution(vector<int> nodes, vector<vector<int>> edges)
{
	vector<int> answer(2);

	const int MAX_NODE_NUM = 1000000;

	int n = nodes.size();
	int m = edges.size();

	vector<int> nodeMap(MAX_NODE_NUM + 1);
	for (int i = 0; i < n; i++)
		nodeMap[nodes[i]] = i;

	vector<vector<int>> graph(n);
	for (auto &e : edges)
	{
		graph[nodeMap[e[0]]].push_back(nodeMap[e[1]]);
		graph[nodeMap[e[1]]].push_back(nodeMap[e[0]]);
	}

	// ===== 추가 시작 : 트리별 위반 노드 카운팅으로 루트 후보 수 계산 =====
	vector<bool> visited(n);
	for (int i = 0; i < n; i++)
	{
		if (visited[i])
			continue;

		queue<int> q;
		q.push(i);
		visited[i] = true;

		// 현재 순회하는 트리 인덱스모음
		vector<int> tree;

		// 각 노드가 부모가 아닐 때 역홀/짝, 홀/짝 개수
		int revCount = 0, normalCount = 0;
		int revRoot = -1, normalRoot = -1;
		while(!q.empty()){
			int cur = q.front(); q.pop();

			tree.push_back(cur);

			// 부모 제외 타입(현재노드가 루트가 아님)
			TYPE nonRootType = GetType(nodes[cur], graph[cur].size() - 1);

			if(nonRootType == EVEN || nonRootType == ODD) {
				normalCount++;
				normalRoot = cur;
			}
			else {
				revCount++;
				revRoot = cur;
			}

			for(int next : graph[cur]){
				if(!visited[next]){
					visited[next] = true;
					q.push(next);
				}
			}
		}

		// 홀짝 트리(answer[0]) 판정 : revCount(안 맞는 개수) 기준
		if(revCount == 0){
			for(int root : tree){
				TYPE rootType = GetType(nodes[root], graph[root].size());
				if(rootType == EVEN || rootType == ODD) answer[0]++;
			}
		}
		else if(revCount == 1) {
			TYPE rootType = GetType(nodes[revRoot], graph[revRoot].size());
			if(rootType == EVEN || rootType == ODD) answer[0]++;
		}

		// 역홀짝 트리(answer[1]) 판정 : normalCount(안 맞는 개수) 기준
		if(normalCount == 0){
			for(int root : tree){
				TYPE rootType = GetType(nodes[root], graph[root].size());
				if(rootType == R_EVEN || rootType == R_ODD) answer[1]++;
			}
		}
		else if(normalCount == 1){
			TYPE rootType = GetType(nodes[normalRoot], graph[normalRoot].size());
			if(rootType == R_EVEN || rootType == R_ODD) answer[1]++;
		}
	}


	return answer;
}
