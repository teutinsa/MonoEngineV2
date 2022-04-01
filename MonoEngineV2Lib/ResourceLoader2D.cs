using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public static class ResourceLoader2D
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Image LoadImage(ResourceManager manager, string name, string filename);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Image LoadImage(ResourceManager manager, string name, byte[] data);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern SolidColorBrush LoadSolidColorBrush(ResourceManager manager, string name, ColorF color);
    }
}
