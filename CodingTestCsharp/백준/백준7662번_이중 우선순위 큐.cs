namespace 백준7662번_이중_우선순위_큐
{
    class Program
    {
        static string solution(string[] opers)
        {
            // 최대 힙
            PriorityQueue<int, int> maxFristPq = new PriorityQueue<int, int>();
            // 최소 힙
            PriorityQueue<int, int> minFirstPq = new PriorityQueue<int, int>();
            // 중복 값 처리
            Dictionary<int, int> valueMap = new Dictionary<int, int>();

            for (int i = 0; i < opers.Length; i++)
            {
                string[] oper = opers[i].Split(" ");

                if (oper[0][0] == 'I')
                {
                    int value = int.Parse(oper[1]);

                    // 오버플로우 처리
                    // -2^31 <= value < 2^31 
                    maxFristPq.Enqueue(value, value == int.MinValue ? int.MaxValue : -value);
                    minFirstPq.Enqueue(value, value);
                    if (!valueMap.ContainsKey(value))
                        valueMap[value] = 1;
                    else
                        valueMap[value]++;
                }
                else
                {
                    int option = int.Parse(oper[1]);
                    // 최소 값 빼기
                    if (option == -1)
                    {
                        while (minFirstPq.Count > 0)
                        {
                            int value = minFirstPq.Dequeue();
                            if (!valueMap.ContainsKey(value))
                                continue;
                            if (--valueMap[value] <= 0)
                                valueMap.Remove(value);
                            break;
                        }
                    }
                    // 최대 값 빼기
                    else
                    {
                        while (maxFristPq.Count > 0)
                        {
                            int value = maxFristPq.Dequeue();
                            if (!valueMap.ContainsKey(value))
                                continue;
                            if (--valueMap[value] <= 0)
                                valueMap.Remove(value);
                            break;
                        }
                    }
                }
            }

            // 양쪽 큐 동기화
            while (minFirstPq.Count > 0
                && (!valueMap.ContainsKey(minFirstPq.Peek()) || valueMap[minFirstPq.Peek()] <= 0))
            {
                minFirstPq.Dequeue();
            }
            while (maxFristPq.Count > 0
                && (!valueMap.ContainsKey(maxFristPq.Peek()) || valueMap[maxFristPq.Peek()] <= 0))
            {
                maxFristPq.Dequeue();
            }

            if (minFirstPq.Count == 0 || maxFristPq.Count == 0)
                return "EMPTY";
            else
                return $"{maxFristPq.Peek()} {minFirstPq.Peek()}";
        }

        static void Main(string[] argc)
        {
            int t = int.Parse(Console.ReadLine());
            while (t-- > 0)
            {
                int k = int.Parse(Console.ReadLine());
                string[] opers = new string[k];
                for (int i = 0; i < k; i++)
                    opers[i] = Console.ReadLine();

                Console.WriteLine(solution(opers));
            }
        }
    }
}