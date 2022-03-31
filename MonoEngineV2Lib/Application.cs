using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public static class Application
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quit();
    }
}
