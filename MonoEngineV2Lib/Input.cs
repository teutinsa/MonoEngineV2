using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public static class Input
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool GetKey(KeyCode key);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool GetKeyDown(KeyCode key);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool GetKeyUp(KeyCode key);
    }
}
