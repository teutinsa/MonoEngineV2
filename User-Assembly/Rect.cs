using MonoEngineV2Lib;

namespace User_Assembly
{
    public struct Rect
    {
        public float x, y, w, h;

        public Rect(Vector3f p, Vector3f s)
            : this(p.x, p.y, s.x, s.y)
        { }

        public Rect(float _x, float _y, float _w, float _h)
        {
            x = _x;
            y = _y;
            w = _w;
            h = _h;
        }

        public bool Collide(Rect rect)
        {
            float num = MathF.Max(x, rect.x);
            float num2 = MathF.Min(x + w, rect.x + rect.w);
            float num3 = MathF.Max(y, rect.y);
            float num4 = MathF.Min(y + h, rect.y + rect.h);
            return (num2 >= num && num4 >= num3);
        }

        public bool Contains(Vector3f point)
        {
            if (x <= point.x && point.y < x + w && y <= point.y)
                return point.y < y + h;
            return false;
        }

        public override string ToString()
        {
            return $"{{x={x}, y={y}, w={w}, h={h}}}";
        }
    }
}
