using System.Runtime.InteropServices;

namespace MonoEngineV2Lib
{
    [StructLayout(LayoutKind.Sequential)]
    public struct ColorF
    {
        public float r;
        public float g;
        public float b;
        public float a;

        public ColorF(float _r, float _g, float _b, float _a = 1.0f)
        {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }

        public override string ToString()
        {
            return $"{{r={r}, g={g}, b={b}, a={a}}}";
        }
    }
}
