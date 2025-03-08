using System;
using System.Runtime.InteropServices;

class GeometryUtils
{
    public struct Pos
    {
        public float x;
        public float y;
        public Pos(float x, float y)
        {
            this.x = x;
            this.y = y;
        }
    }
    public struct Circle
    {
        public Pos midPoint { get; private set; }
        public float radius { get; private set; }
        public Circle(Pos midPoint, float radius)
        {
            this.midPoint = midPoint;
            this.radius = radius;
        }
        public Circle(float x, float y, float radius)
        {
            midPoint = new Pos(x, y);
            this.radius = radius;
        }
    }
    public struct Edge
    {
        public Pos p1 { get; private set; }
        public Pos p2 { get; private set; }

        public Edge(Pos p1, Pos p2)
        {
            this.p1 = p1;
            this.p2 = p2;
        }
        public Edge(float x1, float y1, float x2, float y2)
        {
            this.p1 = new Pos(x1, y1);
            this.p2 = new Pos(x2, y2);
        }
    }
    static Pos GetVector(Pos p1, Pos p2)
    {
        // return p1p2 Vector
        return new Pos(p2.x - p1.x, p2.y - p1.y);
    }

    static float GetDistance(Pos p1, Pos p2)
    {
        return MathF.Sqrt(MathF.Pow((p2.x - p1.x), 2) + MathF.Pow((p2.y - p1.y), 2));
    }

    static float DotProduct(Pos vec1, Pos vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }
    static float SquareMagnitude(Pos vec)
    {
        return vec.x * vec.x + vec.y * vec.y;
    }

    public static bool IsLineCircleColliding(Edge edge, Circle circle)
    {
        Pos vecAB = GetVector(edge.p1, edge.p2);
        Pos vecAC = GetVector(edge.p1, circle.midPoint);

        // 내적 
        float dot = DotProduct(vecAB, vecAC);
        float sqrtAB = SquareMagnitude(vecAB);

        // 투영계수
        float t = dot / sqrtAB;

        // 수선의 발이 선분 내 위치하는 지
        if (t < 0 || t > 1)
            return false;

        // 수선의 발 좌표
        float px = edge.p1.x + t * (edge.p2.x - edge.p1.x);
        float py = edge.p1.y + t * (edge.p2.y - edge.p1.y);

        return GetDistance(circle.midPoint, new Pos(px, py)) <= circle.radius;
    }
}
class Test
{
    static void Main(string[] args)
    {
        int test = 0;
        do
        {
            test = int.Parse(Console.ReadLine());

            Console.WriteLine("원 : x y r");
            string[] inputCircle = Console.ReadLine().Split(' ');
            GeometryUtils.Circle circle =
                new GeometryUtils.Circle(float.Parse(inputCircle[0]), float.Parse(inputCircle[1]), float.Parse(inputCircle[2]));

            Console.WriteLine("선분 : x1 y1 x2 y2");
            string[] inputEdge = Console.ReadLine().Split(' ');
            GeometryUtils.Edge edge =
                new GeometryUtils.Edge(float.Parse(inputEdge[0]), float.Parse(inputEdge[1]), float.Parse(inputEdge[2]), float.Parse(inputEdge[3]));

            Console.WriteLine(GeometryUtils.IsLineCircleColliding(edge, circle) ? "충돌합니다." : "충돌하지 않습니다.");
        } while (test == 1);
    }
}
