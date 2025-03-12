using System;
using System.Numerics;

namespace 원과_원의_충돌_2
{
    // 원점에서 시작해 방향 벡터를 지나는 원과 충돌확인
    class Program
    {
        public static bool IsCollision(Geometry.Vector2 direction, double radius, Geometry.Circle target, out double colTime)
        {
            colTime = -1;

            Geometry.Vector2 dirNormal = direction.Normalize();

            Geometry.Vector2 targetVec = target.center;
            // 내적
            double dotProduct = Geometry.DotProduct(direction, targetVec);
            double magnitude = Geometry.Magnitude(direction);
            // 투영 벡터의 크기
            double projection = dotProduct / magnitude;

            // 수선의 발 좌표
            Geometry.Vector2 perpFootPos = new Geometry.Vector2(dirNormal.x * projection, dirNormal.y * projection);

            // 수선의 발에서 타겟 원까지의 거리
            double distanceFT = Geometry.GetDistance(perpFootPos, targetVec);
            
            // distacneFT < 움직이는 원의 반지름 + 타겟 원의 반지름
            // 일 경우 두 점에서 만남(충돌)
            if (distanceFT < 2)
                return true;
            
            return false;
        }
    }
}