// 프로그래머스(L4) : 제곱 개수 배열
// 문제
// 1. arr의 인덱스 순서대로 arr[i]를 brr에 연속으로 arr[i]개씩 추가
// 2. brr의 부분 배열 구간의 양 끝을 나타내는 l,r이 주어질 때
//  2-1. K = brr의 l번째 원소부터 r번째 원소까지의 합(l<=r, brr[l-1]+brr[l]+...brr[r-1])
//  2-2. C = 길이가 r-l+1인 brr의 부분 배열 중 합이 K인 부분 배열의 개수
// 3. l, r이 주어질 때, 1차원 정수 배열[K, C]를 return
//
// 조건
// 1.arr길이 N : 1<=N<=10^5
// 2.arr[i] : 1<=arr[i]<=10^5
// 3.brr모든 원소의 합<=10^15
//
// 풀이
// 1.쿼리
//  1-1. K : 구간합 (l~r 원소합)
//        => 블록단위 제곱 누적합 O(1), 구간 탐색(이분탐색)
//  1-2. C : 구간개수 (합이 K, 길이가 r-l+1인 구간 개수)
//        => 변화량, 등차수열 
using System;

public class Solution
{
    public struct Segment
    {
        public long l, r, v;
        public long Length => r - l + 1;
        public Segment(long l, long r, long v)
        {
            this.l = l;
            this.r = r;
            this.v = v;
        }
    }

    public class SegmentManager
    {
        private Segment[] idxMap;
        private long[] prefixSum;
        private long brrLength;
        private int arrLength;
        public SegmentManager(int[] arr)
        {
            arrLength = arr.Length;
            // 각 인덱스가 차지하는 구간 할당
            // brr 위치(l, r)는 1-based, idxMap 배열 인덱스는 0-based
            idxMap = new Segment[arrLength];
            prefixSum = new long[arrLength];

            long pEnd = 0;
            for (int i = 0; i < arrLength; i++)
            {
                long end = pEnd + arr[i];
                idxMap[i] = new Segment(pEnd + 1, end, arr[i]);

                prefixSum[i] = (long)arr[i] * arr[i] + (i == 0 ? 0 : prefixSum[i - 1]);
                pEnd = end;
            }

            brrLength = pEnd;
        }

        // target이 포함되는 idxMap 인덱스
        private int GetSegmentIndex(long target)
        {
            int res = 0;
            int lo = 0, hi = arrLength - 1, mid = 0;
            while(lo <= hi)
            {
                mid = (lo + hi) >> 1;
                if (idxMap[mid].r >= target)
                {
                    res = mid;
                    hi = mid - 1;
                }
                else
                    lo = mid + 1;
            }
            return res;
        }
        // l~r 구간합
        public long QueryK(long l, long r)
        {
            int start = GetSegmentIndex(l);
            int end = GetSegmentIndex(r);

            // 같은 세그먼트에 속한 경우
            if (start == end)
            {
                return idxMap[start].v * (r - l + 1);
            }

            long ret = 0;
            // 앞부분 세그먼트
            ret += idxMap[start].v * (idxMap[start].r - l + 1);
            // 중간(포함) 세그먼트
            ret += prefixSum[end - 1] - prefixSum[start];
            // 뒷부분 세그먼트
            ret += idxMap[end].v * (r - idxMap[end].l + 1);
            return ret;
        }

        // r-l+1길이의 구간 합이 K인 구간 개수
        public long QueryC(long K, long l, long r)
        {
            long len = r - l + 1; 
            long last = brrLength - len + 1; 
            if (last <= 0) return 0;

            long count = 0;
            // 윈도우 시작점
            long s = 1; 

            int i = GetSegmentIndex(s);
            int j = GetSegmentIndex(s + len - 1);

            while (s <= last)
            {
                // 윈도우 끝점
                long end = Math.Min(idxMap[i].r, Math.Min(idxMap[j].r - len + 1, last));

                long currentSum = QueryK(s, s + len - 1);
                long diff = K - currentSum;

                // 윈도우 변화량(기울기)
                long d = idxMap[j].v - idxMap[i].v;

                // d == 0 : 구간 안에서 합이 일정하므로 currentSum == K 이면 구간 전체(end - s + 1개)가 해
                if (d == 0 && diff == 0)
                {
                    count += (end - s + 1);
                }
                // d != 0 : f(s + t) = currentSum + t * d (t = 0 ~ end - s)
                // diff = t * d 의 해 t가 정수이고 0 <= t <= end - s 이면 이 구간의 해는 정확히 하나
                else if(d != 0)
                {
                    if (diff % d == 0)
                    {
                        long step = diff / d;
                        if (step >= 0 && step <= end - s)
                        {
                            count++;
                        }
                    }
                }

                // 다음 탐색 구간으로 이동
                s = end + 1;
                if (s <= last)
                {
                    i = GetSegmentIndex(s);
                    j = GetSegmentIndex(s + len - 1);
                }
            }

            return count;
        }
    }
    public long[] solution(int[] arr, long l, long r)
    {
        long[] answer = new long[2];

        SegmentManager sm = new SegmentManager(arr);
        answer[0] = sm.QueryK(l, r);
        answer[1] = sm.QueryC(answer[0], l, r);
        return answer;
    }
}