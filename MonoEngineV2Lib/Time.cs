using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public static class Time
    {
        public static extern float DeltaTime
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
    }
}
