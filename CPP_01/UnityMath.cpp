// 유니티 수학
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Vector3
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
		if (mgtd == 0) return Vector3(0, 0, 0);
		float inv = 1.0f / mgtd;
		return Vector3(_x * inv, _y * inv, _z * inv);
	}
	Vector3 operator+(const Vector3& v) const { return Vector3(_x + v._x, _y + v._y, _z + v._z); }
	Vector3 operator-(const Vector3& v) const { return Vector3(_x - v._x, _y - v._y, _z - v._z); }
	Vector3 operator*(float f) const { return Vector3(_x * f, _y * f, _z * f); }
	Vector3 operator/(float f) const { return Vector3(_x / f, _y / f, _z / f); }
};

// 2D 벡터
struct Vector2
{
	float _x = 0, _y = 0;
	constexpr Vector2() = default;
	constexpr Vector2(float x, float y) : _x(x), _y(y) {}
	Vector2 operator+(const Vector2& v) const { return Vector2(_x + v._x, _y + v._y); }
	Vector2 operator-(const Vector2& v) const { return Vector2(_x - v._x, _y - v._y); }
	Vector2 operator*(float f) const { return Vector2(_x * f, _y * f); }
	Vector2 operator/(float f) const { return Vector2(_x / f, _y / f); }
	// 법선 벡터 (90도 회전)
	Vector2 Normal() const { return Vector2(-_y, _x); }
};

class Geometry
{
public:
	static float Dot(const Vector3& a, const Vector3& b)
	{
		return a._x * b._x + a._y * b._y + a._z * b._z;
	}
	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		return Vector3(
			a._y * b._z - a._z * b._y,
			a._z * b._x - a._x * b._z,
			a._x * b._y - a._y * b._x
		);
	}

	// 2D 벡터곱/법선 (스칼라)
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return a._x * b._x + a._y * b._y;
	}
	static float Cross(const Vector2& a, const Vector2& b)
	{
		return a._x * b._y - a._y * b._x;
	}
};

// 볼록 다각형 (SAT 충돌 판정 대상)
struct Polygon
{
	vector<Vector2> vertices;

	// 분리축(각 변에 수직인 법선) 반환
	vector<Vector2> GetSAT() const
	{
		int size = (int)vertices.size();
		vector<Vector2> axes(size);
		for (int i = 0; i < size; i++)
			axes[i] = (vertices[(i + 1) % size] - vertices[i]).Normal();
		return axes;
	}

	// 이 폴리곤을 axis에 투영한 범위 {min, max}
	pair<float, float> GetProjectionRange(const Vector2& axis) const
	{
		float dot = Geometry::Dot(axis, vertices.front());
		pair<float, float> range = { dot, dot };

		for (int i = 1; i < (int)vertices.size(); i++)
		{
			dot = Geometry::Dot(axis, vertices[i]);
			range.first = min(range.first, dot);
			range.second = max(range.second, dot);
		}
		return range;
	}

	// AABB 범위 {가로 구간, 세로 구간}
	pair<pair<float, float>, pair<float, float>> GetAABBRange() const
	{
		Vector2 p = vertices.front();
		pair<float, float> hzt = { p._x, p._x };
		pair<float, float> vtc = { p._y, p._y };

		for (int i = 1; i < (int)vertices.size(); i++)
		{
			hzt = { min(hzt.first, vertices[i]._x), max(hzt.second, vertices[i]._x) };
			vtc = { min(vtc.first, vertices[i]._y), max(vtc.second, vertices[i]._y) };
		}
		return { hzt, vtc };
	}
};

// 브로드페이즈(AABB) + 내로우페이즈(OBB/SAT) 충돌 검사
class CollisionSystem
{
	static bool CheckOverlaps(const pair<float, float>& r1, const pair<float, float>& r2)
	{
		return !(r1.first > r2.second || r1.second < r2.first);
	}

public:
	// AABB로 충돌 가능성이 있는 폴리곤 쌍 필터링
	// 인접 그래프 형태 반환(단방향, 서로 중복 제거)
	static vector<vector<int>> BroadPhase(const vector<Polygon>& polygons)
	{
		int size = (int)polygons.size();

		vector<pair<pair<float, float>, pair<float, float>>> aabbRanges(size);
		for (int i = 0; i < size; i++) aabbRanges[i] = polygons[i].GetAABBRange();

		vector<vector<int>> graph(size);
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (CheckOverlaps(aabbRanges[i].first, aabbRanges[j].first)
					&& CheckOverlaps(aabbRanges[i].second, aabbRanges[j].second))
					graph[i].push_back(j);
			}
		}
		return graph;
	}

	// SAT 기반 정밀 충돌 판정 (sat1/sat2는 미리 구해둔 분리축 캐시)
	static bool CheckOBBCollision(const Polygon& poly1, const vector<Vector2>& sat1, const Polygon& poly2, const vector<Vector2>& sat2)
	{
		auto axes = sat1;
		axes.insert(axes.end(), sat2.begin(), sat2.end());

		for (auto& axis : axes)
		{
			auto range1 = poly1.GetProjectionRange(axis);
			auto range2 = poly2.GetProjectionRange(axis);

			if (!CheckOverlaps(range1, range2))
				return false;
		}
		return true;
	}

	// 월드 내 모든 폴리곤에 대한 충돌체크 결과
	// 인접 그래프 형태 반환(양방향, 서로 중복 포함)
	static vector<vector<int>> GetCollision(const vector<Polygon>& polygons)
	{
		int size = (int)polygons.size();
		vector<vector<int>> result(size);

		// AABB 브로드페이즈 그래프
		vector<vector<int>> bpGraph = BroadPhase(polygons);

		// 분리축 캐싱
		vector<vector<Vector2>> sats(size);
		for (int i = 0; i < size; i++)
		{
			if (bpGraph[i].size() == 0) continue;
			if (sats[i].size() == 0) sats[i] = polygons[i].GetSAT();

			// AABB 브로드페이즈로 필터링된 쌍에 한해 OBB 체크
			for (int j : bpGraph[i])
			{
				if (sats[j].size() == 0) sats[j] = polygons[j].GetSAT();

				if (CheckOBBCollision(polygons[i], sats[i], polygons[j], sats[j]))
				{
					result[i].push_back(j);
					result[j].push_back(i);
				}
			}
		}
		return result;
	}
};
