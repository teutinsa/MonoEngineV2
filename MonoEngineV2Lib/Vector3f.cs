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

        public override string ToString()
        {
            return $"{{x={x}, y={y}, z={z}}}";
        }
    }
}