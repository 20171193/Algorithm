// 백준 11664번 : 선분과 점(https://www.acmicpc.net/problem/11664)
// 조건
// 1. 3차원에서 선분과 점 사이의 거리의 최솟값
// 2. 좌표p(0<=p<= 10,000)
// 3. 절대/상대 오차는 10^-6까지 허용
// 
// 풀이
// 1. 내적/투영
// 2. 내적(범위), 외적(수선)
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

typedef long double ld;

struct Vec3 {
	ld x, y, z;
	Vec3() {}
	Vec3(ld x, ld y, ld z) : x(x), y(y), z(z) {}
	Vec3 operator+(const Vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }
	Vec3 operator-(const Vec3& from) const { return { x - from.x, y - from.y, z - from.z }; }
	Vec3 operator*(ld v) const { return { x * v, y * v, z * v }; }
	Vec3 cross(const Vec3& other) const {
		return {
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		};
	}
	ld dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; };
	ld magnitude() const {
		if (x == 0 && y == 0 && z == 0) return 0;
		return sqrt(x * x + y * y + z * z);
	}
};

// 내적(투영) 풀이
ld Projection(const Vec3& p1, const Vec3& p2, const Vec3& p3) {
	Vec3 vec12(p2 - p1); // 1-2
	Vec3 vec13(p3 - p1); // 1-3

	// vec12 길이 캐싱
	ld length12 = vec12.magnitude();
	// 내적
	ld dot123 = vec12.dot(vec13);
	// 투영 길이 
	ld projection = dot123 / length12;
	// 비율 (선형 보간)
	ld ratio = projection / length12;

	// 수선의 발 범위 확인 
	if (ratio <= 0) return Vec3(p3 - p1).magnitude();
	else if (ratio >= 1) return Vec3(p3 - p2).magnitude();
	else {
		// 수선의 발 좌표할당 
		Vec3 pos = p1 + (vec12 * ratio);
		// pos-p3 = h(수선, 높이), 최단 거리
		return Vec3(p3 - pos).magnitude();
	}
}

// 내적(범위 체크), 외적 풀이
ld Cross(const Vec3& p1, const Vec3& p2, const Vec3& p3) {
	// 좌표 -> 벡터 
	Vec3 vec12(p2 - p1); // 1-2
	Vec3 vec21(p1 - p2); // 2-1
	Vec3 vec13(p3 - p1); // 1-3
	Vec3 vec23(p3 - p2); // 2-3
	// 내적
	ld dot123 = vec12.dot(vec13); // (1-2) ' (1-3)
	ld dot213 = vec21.dot(vec23); // (2-1) ' (1-3)

	// 내적 부호 판단(둔각)
	// p3이 p1뒤에 위치 -> (p1-p3)이 최소거리
	if (dot123 < 0) return Vec3(p3 - p1).magnitude();
	// p3이 p2뒤에 위치 -> (p2-p3)이 최소거리
	if (dot213 < 0) return Vec3(p3 - p2).magnitude();
	// 외적
	Vec3 crossVec = vec12.cross(vec13);	// (1-2) x (1-3) 
	return crossVec.magnitude() / vec12.magnitude();	// 넓이 / 밑변 = 높이(수선 길이)
}

int main() {
	Vec3 p1, p2, p3;
	cin >> p1.x >> p1.y >> p1.z >> p2.x >> p2.y >> p2.z >> p3.x >> p3.y >> p3.z;
	cout << fixed << setprecision(7) << Projection(p1, p2, p3) << '\n';
	//cout << fixed << setprecision(7) << Cross(p1, p2, p3) << '\n';

	return 0;
}