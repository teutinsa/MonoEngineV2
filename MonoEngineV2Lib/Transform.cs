using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public sealed class Transform : EngineObject
    {
        public extern Vector3f Position
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public extern float Rotation
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public extern Vector3f Scale
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public extern Transform Parent
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public extern GameObject GameObject
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
    }
}