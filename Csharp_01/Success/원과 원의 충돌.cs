using System;
using System.Runtime.CompilerServices;

namespace 원과_원의_충돌
{
    public class CircleCollision
    {
        public static bool IsCollision(Geometry.Circle c1, Geometry.Circle c2)
        {
            Geometry.Vector2 c1c2 = new Geometry.Vector2(c2.x - c1.x, c2.y - c2.y);
            double rSum = c1.radius + c2.radius;

            double dist = Geometry.SquareMagnitude(c1c2);

            //  d > r : 충돌하지 않음
            // d == r : 한 점에서 충돌
            //  d < r : 두 점에서 충돌
            return dist <= rSum * rSum;
        }
    }
}