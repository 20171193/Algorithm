using System;
using System.Net;

namespace 프로그래머스L3_다단계_칫솔_판매
{
    public class Solution
    {
        public class Node
        {
            public int index;
            public string name;

            public Node parent = null;
            public int cost = 0;
            public Node(int index, string name)
            {
                this.index = index;
                this.name = name;
            }
        }
        public void SendCost(ref int[] answer, Node node, int sendCost)
        {
            if (sendCost == 0) return;

            int send = sendCost / 10;
            answer[node.index] += sendCost - send;
            if (node.parent != null)
                SendCost(ref answer, node.parent, send);
        }
        public int[] solution(string[] enroll, string[] referral, string[] seller, int[] amount)
        {
            int n = enroll.Length;
            int[] answer = new int[n];

            Dictionary<string, Node> nameNodeMap = new Dictionary<string, Node>();
            Dictionary<int, Node> indexNodeMap = new Dictionary<int, Node>();
            for (int i = 0; i < n; i++)
            {
                Node node = new Node(i, enroll[i]);
                nameNodeMap[enroll[i]] = node;
                indexNodeMap[i] = node;
            }

            for (int i = 0; i < n; i++)
            {
                if (referral[i][0] == '-') continue;
                indexNodeMap[i].parent = nameNodeMap[referral[i]];
            }

            for (int i = 0; i < seller.Length; i++)
            {
                SendCost(ref answer, nameNodeMap[seller[i]], amount[i] * 100);
            }

            return answer;
        }
    }
}