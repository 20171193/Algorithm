#include <iostream>
#include <bitset>
using namespace std;

int n, k, ret;

int main() {

	cin >> n >> k;
	// 켜져있는 bit 카운팅
	while (bitset<32>(n + ret).count() > k)
		ret++;

	cout << ret << '\n';
	return 0;
}