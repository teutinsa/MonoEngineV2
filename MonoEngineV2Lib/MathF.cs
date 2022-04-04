using System;

namespace MonoEngineV2Lib
{
    public static class MathF
    {
        public static float Clamp(float value, float min, float max)
        {
            return value < min ? min : value > max ? max : value;
        }

        public static float Min(float v1, float v2)
        {
            return v1 < v2 ? v1 : v2;
        }

        public static float Max(float v1, float v2)
        {
            return v1 > v2 ? v1 : v2;
        }
    }
}
