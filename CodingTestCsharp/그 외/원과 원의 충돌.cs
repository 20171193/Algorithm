using System;
using System.Runtime.CompilerServices;

namespace 원과_원의_충돌
{
    public static class Geometry
    {
        public struct Vector2
        {
            public double x;
            public double y;
            public Vector2(double x, double y)
            {
                this.x = x;
                this.y = y;
            }
        }
        public struct Circle
        {
            public Vector2 center;
            public double radius;
            public double x {get { return center.x; } }
            public double y {get { return center.y; } } 
            public Circle(Vector2 center, double radius)
            {
                this.center = center;
                this.radius = radius;
            }
            public Circle(double x, double y, double radius)
            {
                center = new Vector2(x, y);
                this.radius = radius;
            }
        }
        public static double SquareMagnitude(this Vector2 vec)
        {
            return vec.x * vec.x + vec.y * vec.y;
        }
    }

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