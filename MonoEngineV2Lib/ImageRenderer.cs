using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public sealed class ImageRenderer : Component
    {
        public extern Image Image
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public extern Vector2f Size
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
