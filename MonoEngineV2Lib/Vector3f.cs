using System.Runtime.InteropServices;

namespace MonoEngineV2Lib
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3f
    {
        public float x;
        public float y;
        public float z;

        public Vector3f(float _x, float _y, float _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }

        public Vector3f(float _x, float _y)
            : this(_x, _y, 0.0f)
        { }

        public static Vector3f operator +(Vector3f a, Vector3f b)
        {
            return new Vector3f(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        public static Vector3f operator +(Vector3f v, float f)
        {
            return new Vector3f(v.x + f, v.y + f, v.z + f);
        }

        public static Vector3f operator -(Vector3f a, Vector3f b)
        {
            return new Vector3f(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        public static Vector3f operator -(Vector3f v, float f)
        {
            return new Vector3f(v.x - f, v.y - f, v.z - f);
        }

        public static Vector3f operator *(Vector3f a, Vector3f b)
        {
            return new Vector3f(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        public static Vector3f operator *(Vector3f v, float f)
        {
            return new Vector3f(v.x * f, v.y * f, v.z * f);
        }

        public static Vector3f operator /(Vector3f a, Vector3f b)
        {
            return new Vector3f(a.x / b.x, a.y / b.y, a.z / b.z);
        }

        public static Vector3f operator /(Vector3f v, float f)
        {
            return new Vector3f(v.x / f, v.y / f, v.z / f);
        }

        public override string ToString()
        {
            return $"{{x={x}, y={y}, z={z}}}";
        }
    }
}