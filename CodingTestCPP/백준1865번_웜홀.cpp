// ���� 1865�� ��Ȧ
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int INF = 987654321;
int tc, n, m, w, s, e, t;
// ���� ����Ŭ ã��
// ��������

bool HasCycle(const unordered_map<int, vector<pair<int, int>>> edges)
{
	vector<int> dists(n + 1, INF);
	dists[1] = 0;

	// ���� �׷����� �ƴ� �� ����
	// (Ž�� �������� ������ �� ������ ��带 ���� ���� ����)
	for (int i = 1; i <= n; i++)
	{
		if (dists[i] != INF)
			continue;
		dists[i] = 0;
		// n-1�� Ž��
		for (int j = 1; j < n; j++)
		{
			// ������ ���°��
			if (edges.find(j) == edges.end()) continue;

			for (auto iter = edges.begin(); iter != edges.end(); iter++)
			{
				s = (*iter).first;
				// ��ΰ� ���� ���
				if (dists[s] == INF) continue;

				for (auto _iter = (*iter).second.begin(); _iter != (*iter).second.end(); _iter++)
				{
					e = (*_iter).first;
					t = (*_iter).second;

					dists[e] = min(dists[e], dists[s] + t);
				}
			}
		}
	}
	// ����Ŭ Ȯ��
	for (auto iter = edges.begin(); iter != edges.end(); iter++)
	{
		s = (*iter).first;
		// ��ΰ� ���� ���
		if (dists[s] == INF) continue;
		for (auto _iter = (*iter).second.begin(); _iter != (*iter).second.end(); _iter++)
		{
			e = (*_iter).first;
			t = (*_iter).second;

			// ���� ����Ŭ �߰�
			if (dists[e] > dists[s] + t)
				return true;
		}
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> tc;
	while (tc--)
	{
		cin >> n >> m >> w;

		// ���� �Ҵ� (�����)
		unordered_map<int, vector<pair<int, int>>> edges;
		for (int i = 0; i < m; i++)
		{
			cin >> s >> e >> t;
			if (edges.find(s) == edges.end())
				edges.insert({ s, {{e,t}} });
			else
				edges[s].push_back({ e,t });

			if (edges.find(e) == edges.end())
				edges.insert({ e, {{s,t}} });
			else
				edges[e].push_back({ s,t });

		}

		// ��Ȧ �Ҵ� (�ܹ���)
		for (int i = 0; i < w; i++)
		{
			cin >> s >> e >> t;
			if (edges.find(s) == edges.end())
				edges.insert({ s, {{e,-t}} });
			else
				edges[s].push_back({ e,-t });
		}

		if (HasCycle(edges))
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}

	return 0;
}