#include <iostream>
#include <bitset>
using namespace std;

int n, k, ret;

int main() {

	cin >> n >> k;
	// �����ִ� bit ī����
	while (bitset<32>(n + ret).count() > k)
		ret++;

	cout << ret << '\n';
	return 0;
}