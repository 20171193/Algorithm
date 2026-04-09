using System;
using System.Collections;
using System.Runtime.CompilerServices;
using System.Text;

namespace 백준10866번_덱
{
    class Program
    {
        // 입력
        const string push = "push";
        const string pop = "pop";
        const string size = "size";
        const string empty = "empty";
        const string front = "front";
        const string back = "back";

        class Deque<T>
        {
            const int DEFAULT_CAPACITY = 16;

            private T[] arr;
            private int head;
            private int tail;
            private int count;

            public int Capacity => arr.Length;
            public int Size => count;
            public bool IsFull => (tail + 1) % Capacity == head;
            public bool IsEmpty => count == 0;

            public bool Front(out T value)
            {
                value = default;
                if (count < 1)
                    return false;
                else
                {
                    value = arr[head];
                    return true;
                }
            }
            public bool Back(out T value)
            {
                value = default;
                if (count < 1)
                    return false;
                else
                {
                    value = arr[(tail - 1 + Capacity) & (Capacity - 1)];
                    return true;
                }
            }

            public Deque(int capacity = DEFAULT_CAPACITY)
            {
                if (capacity <= 0)
                    capacity = DEFAULT_CAPACITY;

                arr = new T[capacity];
                head = 0;
                tail = 0;
                count = 0;
            }

            public void Push_Front(T value)
            {
                if (IsFull)
                    Extend();

                head = (head - 1) & (Capacity - 1);
                arr[head] = value;
                count++;
            }
            public void Pop_Front()
            {
                if (IsEmpty)
                    return;

                arr[head] = default;
                head = (head + 1) & (Capacity - 1);
                count--;
            }
            public void Push_Back(T value)
            {
                if (IsFull)
                    Extend();

                arr[tail] = value;
                tail = (tail + 1) & (Capacity - 1);
                count++;
            }
            public void Pop_Back()
            {
                if (IsEmpty)
                    return;

                tail = (tail - 1) & (Capacity - 1);
                arr[tail] = default;
                count--;
            }

            private void Extend()
            {
                int newCapacity = Capacity << 1;
                T[] newArr = new T[newCapacity];

                for (int i = 0; i < count; i++)
                    newArr[i] = arr[(i + head) & (Capacity - 1)];

                arr = newArr;
                head = 0;
                tail = count;
            }
        }

        static string solution(string[] opers)
        {
            StringBuilder answers = new StringBuilder();

            Deque<int> deque = new Deque<int>();

            for (int i = 0; i < opers.Length; i++)
            {
                string str = opers[i].ToString();

                if (str.Substring(0, 4) == push)
                {
                    string[] oper = str.Split(' ', '_');
                    if (oper[1] == front)
                        deque.Push_Front(int.Parse(oper[2]));
                    else
                        deque.Push_Back(int.Parse(oper[2]));
                }
                else if (str.Substring(0, 3) == pop)
                {
                    string[] oper = str.Split(' ', '_');
                    if (oper[1] == front)
                    {
                        if (deque.Front(out int value))
                        {
                            answers.AppendLine($"{value}");
                            deque.Pop_Front();
                        }
                        else
                            answers.AppendLine("-1");
                    }
                    else
                    {
                        if (deque.Back(out int value))
                        {
                            answers.AppendLine($"{value}");
                            deque.Pop_Back();
                        }
                        else
                            answers.AppendLine("-1");
                    }
                }
                else if (str == size)
                    answers.AppendLine($"{deque.Size}");
                else if (str == empty)
                    answers.AppendLine(deque.IsEmpty ? "1" : "0");
                else if (str == front)
                {
                    if (deque.Front(out int value))
                        answers.AppendLine($"{value}");
                    else
                        answers.AppendLine("-1");
                }
                else if (str == back)
                {
                    if (deque.Back(out int value))
                        answers.AppendLine($"{value}");
                    else
                        answers.AppendLine("-1");
                }
            }

            return answers.ToString();
        }

        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());

            string[] opers = new string[n];
            for (int i = 0; i < n; i++)
                opers[i] = Console.ReadLine();

            Console.WriteLine(solution(opers));
        }
    }
}