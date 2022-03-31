using System.Runtime.InteropServices;

namespace MonoEngineV2Lib
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector2f
    {
        public float x;
        public float y;

        public Vector2f(float _x, float _y)
        {
            x = _x;
            y = _y;
        }
    }
}