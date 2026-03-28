// 백준 20366번 : 같이 눈사람 만들래?
// 조건
// 1. 눈사람 하나에 눈덩이 2개 사용
// 2. n(4<=n<=600)개의 눈덩이 중 4개로 눈사람을 2개 만들었을 때,
//    두 눈사람 키 차이의 최솟값
// 3. 눈덩이 지름h(1<=h<=10^9)
// 풀이
// 1. 조합 600C4 > 2^31 불가  
// 2. 투포인터 n^2
#include <iostream>
#include <algorithm>
using namespace std;

int n, arr[601];

int solution(){
    int ret = 1000000000;
    sort(arr, arr+n);

    for(int i = 0; i < n; i++){
        for(int j = n-1; j > i; j--){
            int a = arr[i]+arr[j];
            
            int l = 0;
            int r = n-1;
            while(l < r){
                if(l == i || l == j) l++;
                if(r == i || r == j) r--;
                if(l >= r) break;

                int b = arr[l] + arr[r];
                int diff = abs(a-b);
                ret = min(ret, diff);

                if(b < a) l++;
                else r--;
            }
        }
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i =0; i<n; i++) 
        cin >> arr[i];

    cout << solution() << '\n';
    return 0;
}