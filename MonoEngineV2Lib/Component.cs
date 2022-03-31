using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public class Component : EngineObject
    {
        public extern GameObject GameObject
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
    }
}