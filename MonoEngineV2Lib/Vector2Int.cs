using System.Runtime.InteropServices;

namespace MonoEngineV2Lib
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector2Int
    {
        public int x;
        public int y;

        public Vector2Int(int _x, int _y)
        {
            x = _x;
            y = _y;
        }
    }
}
