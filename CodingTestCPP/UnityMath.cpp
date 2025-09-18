// 게임 수학
#include <math.h>
using namespace std;

static struct Vector3
{
	float _x = 0, _y = 0, _z = 0;
	constexpr Vector3() = default;
	constexpr Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}
	void Zero() { *this = Vector3(0, 0, 0); }
	float sqrMagnitude() { return _x * _x + _y * _y + _z * _z; }
	float Magnitude() { return sqrt(sqrMagnitude()); }
	void Normalize()
	{
		float mgtd = Magnitude();
		if (mgtd == 0) { Zero(); return; }
		float inv = 1.0f / mgtd;
		_x *= inv;
		_y *= inv;
		_z *= inv;
	}
	Vector3 normalized()
	{
		float mgtd = Magnitude();
		if (mgtd == 0) { Zero(); return; }
		float inv = 1.0f / mgtd;
		return Vector3(_x * inv, _y * inv, _z * inv);
	}
	Vector3 operator+(const Vector3& v) const { return Vector3(_x + v._x, _y + v._y, _z + v._z); }
	Vector3 operator-(const Vector3& v) const { return Vector3(_x - v._x, _y - v._y, _z - v._z); }
	Vector3 operator*(float f) const { return Vector3(_x * f, _y * f, _z * f); }
	Vector3 operator/(float f) const { return Vector3(_x / f, _y / f, _z / f); }
};

class Geometry
{

};