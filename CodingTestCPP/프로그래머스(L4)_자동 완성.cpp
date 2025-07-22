// 프로그래머스(L4), 카카오(3차) : 자동 완성
#include <string> 
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
using namespace std;

// 사전 순 트리 형태로 구성
struct Node
{
    unordered_map<char, unique_ptr<Node>> children;
    int count = 0;
    bool isEnd = false;
};

void Insert(const string& word, Node* root)
{
    Node* cur = root;
    for (char c : word)
    {
        auto& children = cur->children;
        auto it = children.find(c);
        if (it == children.end())
        {
            auto result = children.insert({ c, make_unique<Node>() });
            it = result.first;
        }

        cur = (*it).second.get();
        cur->count++;
    }
    cur->isEnd = true;
}

int solution(vector<string> words) {
    int answer = 0;

    Node* root = new Node();

    sort(words.begin(), words.end());
    for (const string& w : words)
        Insert(w, root);

    for (const string& w : words)
    {
        Node* cur = root;
        int cnt = 0;

        for (char c : w)
        {
            cur = cur->children[c].get();
            cnt++;

            if (cur->count == 1)
                break;
        }

        answer += cnt;
    }

    delete root;
    return answer;
}