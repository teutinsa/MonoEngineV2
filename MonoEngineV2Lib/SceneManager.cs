using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public static class SceneManager
    {
        public static extern Scene CurrentScene
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
    }
}
