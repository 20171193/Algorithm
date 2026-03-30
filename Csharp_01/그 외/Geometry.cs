public static class Geometry
{
    public struct Vector3
    {
        public double X { get; }
        public double Y { get; }
        public double Z { get; }
        public Vector3(double x, double y, double z)
        {
            X = x;
            Y = y;
            Z = z;
        }
        public Vector3() : this(0,0, 0){ }
    }
    public struct Vector2
    {
        public double X { get; }
        public double Y { get; }
        public Vector2(double x, double y)
        {
            X = x;
            Y = y;
        }
        public Vector2() : this(0, 0){ }
    }
    public struct Circle
    {
        public Vector2 center;
        public double radius;
        public double x { get { return center.x; } }
        public double y { get { return center.y; } }
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
        return vec.X * vec.X + vec.Y * vec.Y;
    }
    public static double Magnitude(this Vector2 vec)
    {
        return Math.Sqrt(SquareMagnitude(vec));
    }
    public static Vector2 Normalize(this Vector2 vec)
    {
        double magnitude = Magnitude(vec);
        if (magnitude == 0)
            return new Vector2();
        else
            return new Vector2(vec.X / magnitude, vec.Y / magnitude);    
    }
    public static double DotProduct(Vector2 vec1, Vector2 vec2)
    {
        return vec1.X * vec2.X + vec1.Y * vec2.Y;
    }
    public static double GetSqrDistance(Vector2 vec1, Vector2 vec2)
    {
        return (vec2.X - vec1.X) * (vec2.X - vec1.X) + (vec2.Y - vec1.Y) * (vec2.Y - vec1.Y);
    }
    public static double GetDistance(Vector2 vec1, Vector2 vec2)
    {
        return Math.Sqrt(GetSqrDistance(vec1, vec2));
    }
}
